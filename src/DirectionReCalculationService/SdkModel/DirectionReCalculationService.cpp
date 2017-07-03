// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "DirectionReCalculationService.h"

#include <vector>
#include "RouteRepository.h"
#include "Routes.h"

namespace ExampleApp
{
    namespace DirectionReCalculationService
    {
        namespace SdkModel
        {
            
            DirectionReCalculationService::DirectionReCalculationService( Eegeo::Location::ILocationService& locationService,ExampleApp::PathDrawing::IPathDrawingController& pathDrawingController,ExampleAppMessaging::TMessageBus& messageBus,Eegeo::Routes::RouteRepository& routeRepository)
            : m_locationService(locationService)
            , m_pathDrawingController(pathDrawingController)
            , m_messageBus(messageBus)
            , m_shouldReCalculate(false)
            , m_directionsMenuStateChangedCallback(this, &DirectionReCalculationService::OnDirectionsMenuStateChanged)
            , m_routeRepository(routeRepository)
            {
                m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
            }
            
            DirectionReCalculationService::~DirectionReCalculationService()
            {
                m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);
            }
            
            void DirectionReCalculationService::OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message)
            {
                if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Inactive)
                {
                    m_shouldReCalculate = false;
                }
            }

            
            void DirectionReCalculationService::Update(float dt)
            {
               
                std::vector<const Eegeo::Routes::Route*> routes = m_routeRepository.GetRoutes();
                if (routes.size() > 0)
                {
                    const Eegeo::Routes::Route* route = routes[0];
                    Eegeo::Space::LatLong currentLatLong = Eegeo::Space::LatLong::FromDegrees(0.0, 0.0);
                    m_locationService.GetLocation(currentLatLong);
                    const Eegeo::Space::LatLongAltitude firstLatLong = Eegeo::Space::LatLongAltitude::FromDegrees(currentLatLong.GetLatitudeInDegrees(), currentLatLong.GetLongitudeInDegrees(),0.0);
                    double out_closestApproch;
                    int out_immedeiatly_before;
                    double distance = Eegeo::Routes::Route::DistanceToRoute(route->GetPoints(),firstLatLong.ToECEF(),out_closestApproch,out_immedeiatly_before);
                    if (distance < 1.0)
                    {
                        m_shouldReCalculate = true;
                    }
                    if (distance >= 2.0 && m_shouldReCalculate == true)
                    {
                        // call for recalculations
                        const std::vector<Eegeo::Routes::RouteVertex>& points = route->GetPoints();
                        if (points.size() > 0)
                        {
                            const Eegeo::Routes::RouteVertex lastPoint = points[points.size()-1];
                            m_pathDrawingController.RemoveRoutePlan();
                            m_messageBus.Publish(ExampleApp::DirectionsMenu::DirectionMenuFindDirectionMessage(firstLatLong,Eegeo::Space::LatLongAltitude::FromLatLong(lastPoint.GetLocation(), 0),-1,-1,true,"",""));


                        }
                    }
                }
            }
        }
    }
}
