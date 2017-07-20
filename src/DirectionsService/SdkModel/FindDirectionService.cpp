// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "SearchResultModel.h"
#include "FindDirectionService.h"
#include "DirectionQueryResponseReceivedMessage.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

#include "RouteService.h"
#include "Route.h"
#include "LinearAltitudeBasedRouteThicknessPolicy.h"
#include "RouteStyle.h"
#include "RouteRepository.h"
#include <vector>
#include "AppInteriorCameraWrapper.h"
#include "RenderCamera.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            FindDirectionService::FindDirectionService(FindDirectionHttpRequestFactory& findDirectionHttpRequestFactory,Eegeo::Routes::Webservice::JsonRouteParser& resultParser,Eegeo::Routes::RouteService& routeService,Eegeo::Routes::RouteRepository& routeRepository,Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,FindDirectionResultJsonParser& findDirectionResultParser,Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,ExampleAppMessaging::TMessageBus& messageBus, AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper)
            : m_pCurrentRequest(NULL)
            , m_findDirectionHttpRequestFactory(findDirectionHttpRequestFactory)
            , m_handleResponseCallback(this,&FindDirectionService::HandleRouteDirectionResponse)
            , m_findDirectionResultParser(findDirectionResultParser)
            , m_resultParser(resultParser)
            , m_failAlertHandler(this, &FindDirectionService::OnFailedToCallRouteResponse)
            , m_alertBoxFactory(alertBoxFactory)
            , m_messageBus(messageBus)
            , m_routeService(routeService)
            , m_routeRepository(routeRepository)
//            , m_pInteriorInteractionModel(interiorInteractionModel)
            , m_directionsMenuStateChangedCallback(this, &FindDirectionService::OnDirectionsMenuStateChanged)
            , m_onFindNewDirectionCallback(this, &FindDirectionService::OnFindNewDirection)
            , m_appModeChangedCallback(this, &FindDirectionService::OnAppModeChanged)
            , m_pIsInteriorRoute(false)
            , m_routes (NULL)
            , m_cameraWrapper(cameraWrapper)


            {
                m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
                m_messageBus.SubscribeNative(m_onFindNewDirectionCallback);

                m_messageBus.SubscribeUi(m_appModeChangedCallback);

            }
            FindDirectionService::~FindDirectionService()
            {
                m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);
                m_messageBus.UnsubscribeNative(m_onFindNewDirectionCallback);

                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);


            }
            void FindDirectionService::InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback)
            {
                m_findDirectionqueryResponseReceivedCallbacks.AddCallback(callback);
            }
            
            void FindDirectionService::RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback)
            {
                m_findDirectionqueryResponseReceivedCallbacks.RemoveCallback(callback);
            }
            
            void FindDirectionService::PerformLocationQuerySearch(const Direction::SdkModel::FindDirectionQuery& findDirectionQuery)
            {
                // destroy any existing routes
                m_routeService.DestroyAllRoutes();

                if(m_pCurrentRequest != NULL)
                {
                    m_pCurrentRequest->Cancel();
                }
                m_pIsInteriorRoute = findDirectionQuery.IsInterior();
                if (findDirectionQuery.IsInterior())
                {
                    m_routeThicknessPolicy.SetScaleFactor(0.3f);
                    
                }
                else
                {
                    m_routeThicknessPolicy.SetScaleFactor(1.7f);
                }
//                m_routeThicknessPolicy.SetScaleFactor(0.3f);
                m_pCurrentRequest = m_findDirectionHttpRequestFactory.CreateFindDirectionQuery(findDirectionQuery, m_handleResponseCallback);
                m_pCurrentRequest->Dispatch();

            }
            
            void FindDirectionService::HandleRouteDirectionResponse()
            {
                Eegeo_ASSERT(m_pCurrentRequest != NULL, "Find Direction request must have been performed");
                
                if(m_pCurrentRequest->IsSucceeded())
                {
                    const std::string& response(m_pCurrentRequest->ResponseString());
                    DirectionResultModel result =  m_findDirectionResultParser.ParseGeoNamesQueryResults(response);
                    m_messageBus.Publish(DirectionResultSection::DirectionQueryResponseReceivedMessage(result));
                    if(result.GetCode() == "Error" || result.GetRoutes().size() == 0)
                    {
                        m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to obtain route.", "No location found matching.", m_failAlertHandler);
                    }
                    else
                    {
                        
//                        Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleNone, Eegeo::Rendering::LayerIds::AfterWorld);
                        Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleSegmentedWithDirection, Eegeo::Rendering::LayerIds::InteriorEntities, true, 0.0f);

                        // this will asynchronously parse the result and add the resulting route to m_routeService
//                      m_resultParser.CreateRouteFromJSON(response, m_routeService, routeStyle, m_pInteriorInteractionModel);
                        m_resultParser.CreateRouteFromJSON(response, m_routeService, routeStyle);
                        
                        if(result.GetCode() == "Error" || result.GetRoutes().size() == 0)
                        {
                            m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to obtain route.", "No location found matching.", m_failAlertHandler);
                        }
                        
                    }
                    
                }
                else
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to obtain route.", "No location found matching.", m_failAlertHandler);
                }
                m_pCurrentRequest = NULL;
            }
            
            void FindDirectionService::OnFailedToCallRouteResponse()
            {
                
            }

            void FindDirectionService::ClearRoutes()
            {
                m_routeService.DestroyAllRoutes();
            }
            
            void FindDirectionService::OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message)
            {
                if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Inactive)
                {
                    ClearRoutes();
                }
            }
            void FindDirectionService::OnFindNewDirection(const DirectionsMenu::DirectionMenuFindDirectionMessage&)
            {
                ClearRoutes();
            }

            
            void FindDirectionService::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)  // will use for route visibility for different modes otherwise need to remove still facing few issues while regenerating
                                                                                                        //route. Data not exposed.
            {
                if (m_pIsInteriorRoute && message.GetAppMode() == AppModes::SdkModel::InteriorMode)
                {
                    if (m_routes.size() > 0)
                    {
                  
                    }
                  
                }
                else if (m_pIsInteriorRoute)
                {
                    if (m_pIsInteriorRoute)
                    {
                        
                         m_routes = m_routeRepository.GetRoutes();
                    }

                }
                
            }
            
            void FindDirectionService::Update(float dt)
            {

                float altitude = m_cameraWrapper.GetRenderCamera().GetAltitude();
                altitude = 0;
              //  m_routeThicknessPolicy.SetAltitude(altitude);
            }
        }
    }
}
