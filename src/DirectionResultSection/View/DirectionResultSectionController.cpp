// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPointModel.h"
#include "DirectionRouteModel.h"
#include "DirectionResultModel.h"
#include "SearchResultItemModel.h"
#include "DirectionResultSectionController.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace View
        {
            
            DirectionResultSectionController::DirectionResultSectionController(Menu::View::IMenuViewModel& directionMenuViewModel
                                                                               ,Menu::View::IMenuOptionsModel& menuOptionsModel
                                                                               ,ExampleAppMessaging::TMessageBus& messageBus
                                                                               ,const Menu::View::IMenuReactionModel& menuReaction
                                                                               ,SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel)
            : m_directionMenuViewModel(directionMenuViewModel)
            , m_menuOptions(menuOptionsModel)
            , m_messageBus(messageBus)
            , m_directionResultReceivedHandler(this, &DirectionResultSectionController::OnSearchQueryResponseReceivedMessage)
            , m_directionQueryRemovedHandler(this, &DirectionResultSectionController::OnSearchQueryRemovedMessage)
            , m_menuReaction(menuReaction)
            , m_searchResultPoiViewModel(searchResultPoiViewModel)
            , m_directionsMenuStateChangedCallback(this, &DirectionResultSectionController::OnDirectionsMenuStateChanged)
            , m_wayPointCount(0)
            {
                m_messageBus.SubscribeUi(m_directionResultReceivedHandler);
                m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
            }
            
            DirectionResultSectionController::~DirectionResultSectionController()
            {
                m_messageBus.UnsubscribeUi(m_directionResultReceivedHandler);
                m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);
            }
            
            void DirectionResultSectionController::OnSearchQueryResponseReceivedMessage(const DirectionQueryResponseReceivedMessage& message)
            {
                
                RemoveWayPoints();
                
                Direction::SdkModel::DirectionResultModel& model = message.GetDirectionResultModel();
                const std::vector<Direction::SdkModel::DirectionRouteModel>& routes = model.GetRoutes();


                for(int j = 0; j < routes.size(); ++j)
                {
                    
                    Direction::SdkModel::DirectionRouteModel routeModel = routes[j];
                    const std::vector<Direction::SdkModel::DirectionInnerRouteModel>& tempVector = routeModel.GetInnerRoutes();
                    
                    Direction::SdkModel::DirectionInnerRouteModel tempInnerRouteModel = tempVector[0];
                    const std::vector<Direction::SdkModel::LegRouteModel>& innerRouteLegs = tempInnerRouteModel.GetInnerRouteLegs();
                    
                    int routeDuration = tempInnerRouteModel.GetDuration();
                    
                    Eegeo_TTY("Duration: %i",routeDuration);
                    
                    if (innerRouteLegs.size()>0)
                    {
                        const  Direction::SdkModel::LegRouteModel firstLeg = innerRouteLegs[0];
                        const std::vector<Direction::SdkModel::StepRouteModel>& routeStepsVector = firstLeg.GetLegRouteSteps();
                        
                        for (int n = 0; n < routeStepsVector.size(); n++)
                        {
                            
                            const Direction::SdkModel::StepRouteModel stepRouteModel = routeStepsVector[n];
                            
                            const Direction::SdkModel::ManeuverRouteModel &stepManeuver = stepRouteModel.GetManeuverRouteModel();
                            
                            ExampleApp::Search::SdkModel::TagIconKey iconKey = "";
                            if (n == 0)
                            {
                                iconKey = "DirectionCard_RouteStart";
                            }
                            else if (n == routeStepsVector.size()-1)
                            {
                                iconKey = "DirectionCardWayPt_SetRouteEnd";
                            }
                            
                           
                            std::string duration = "Temp Duration";
                            std::string subtitle = std::to_string(routeDuration);
                            const Eegeo::Space::LatLong latlong = stepManeuver.GetLocation();
                            
                            Eegeo::Resources::Interiors::InteriorId m_buildingId(stepRouteModel.GetBuildingID());
                            m_menuOptions.AddItem(std::to_string(stepRouteModel.GetStepID()),
                                                  stepRouteModel.GetStepRouteName(),
                                                  subtitle,
                                                  iconKey,
                                                  duration,
                                                  Eegeo_NEW(SearchResultSection::View::SearchResultItemModel)("model title",
                                                                                                              latlong.ToECEF(),
                                                                                                              stepRouteModel.GetInInterior(),
                                                                                                              true,
                                                                                                              false,
                                                                                                              m_buildingId,
                                                                                                              stepRouteModel.GetLevel(),
                                                                                                              m_directionMenuViewModel,                                                                           m_searchResultPoiViewModel,
                                                                                                              m_wayPointCount,
                                                                                                              m_messageBus,
                                                                                                              m_menuReaction));
                            m_wayPointCount++;

                        
                        }

                    }
                    
                }
                
            }
            void DirectionResultSectionController::OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message)
            {
            }
            
            void DirectionResultSectionController::OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message)
            {
                if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Inactive)
                {
                    RemoveWayPoints();
                }
            }
            
            void DirectionResultSectionController::RemoveWayPoints()
            {
                for(int i = 0; i < m_wayPointCount; ++i)
                {
                    m_menuOptions.RemoveItem(std::to_string(i));
                }
                m_wayPointCount = 0;
            
            }

        }
    }
}


