// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPointModel.h"
#include "DirectionRouteModel.h"
#include "DirectionResultModel.h"
#include "SearchResultItemModel.h"
#include "DirectionResultSectionController.h"
#include <iomanip>
#include <sstream>

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
                int wayPointNumber = 0;
                int leftRightCount = 0;

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
                            
                            ExampleApp::Search::SdkModel::TagIconKey iconKey = GetIconImageName(stepRouteModel);

                            bool isWayPoint = false;
                            
                            double di = stepRouteModel.GetStepRouteDistance();
                            std::stringstream stream;
                            stream << std::fixed << std::setprecision(1) << di;
                            std::string s = stream.str();
                            ExampleApp::PathDrawing::WayPointType::Values wayPointype = ExampleApp::PathDrawing::WayPointType::None;
                            
                            if(stepManeuver.GetType() == "depart" && stepManeuver.GetModifier() == "")
                            {
                                wayPointype = ExampleApp::PathDrawing::WayPointType::Start;
                                wayPointNumber = 17;
                            }
                            else if(stepManeuver.GetType() == "arrive" && stepManeuver.GetModifier() == "")
                            {
                                wayPointype = ExampleApp::PathDrawing::WayPointType::End;
                                wayPointNumber = 18;

                            }
                            else if(stepRouteModel.GetStepType() == "Entrance")
                            {
                                wayPointype = ExampleApp::PathDrawing::WayPointType::Entrance;
                                wayPointNumber = 19;

                            }
                            else if(stepRouteModel.GetStepType() == "Elevator")
                            {
                                wayPointype = ExampleApp::PathDrawing::WayPointType::Elevator;
                                wayPointNumber = 20;

                            }
                            else if (stepManeuver.GetModifier() == "left")
                            {
                                wayPointype = ExampleApp::PathDrawing::WayPointType::Left;
                                leftRightCount++;
                                wayPointNumber = leftRightCount;
                            }
                            else if (stepManeuver.GetModifier() == "right")
                            {
                                wayPointype = ExampleApp::PathDrawing::WayPointType::Right;
                                leftRightCount++;
                                wayPointNumber = leftRightCount;
                            }
                            
                            std::string sTitleCategory = stepRouteModel.GetManeuverRouteModel().GetModifier()+" "+s+"m";
                            
                            if (stepManeuver.GetType() == "depart" || stepManeuver.GetType() == "arrive")
                            {
                                if (stepManeuver.GetModifier() == "right" || stepManeuver.GetModifier() == "left")
                                {
                                    sTitleCategory =  stepManeuver.GetModifier() + " to " +stepRouteModel.GetManeuverRouteModel().GetType();
                                }
                                else
                                {
                                    sTitleCategory = stepRouteModel.GetManeuverRouteModel().GetType();
                                }
                            }
                            
                            std::string duration = "Temp Duration";
                            
                            std::string subtitle = std::to_string(stepRouteModel.GetStepRouteDuration());
                            const Eegeo::Space::LatLong latlong = stepManeuver.GetLocation();
                            
                            Eegeo::Resources::Interiors::InteriorId m_buildingId(stepRouteModel.GetBuildingID());
                            m_menuOptions.AddItem(std::to_string(stepRouteModel.GetStepID()),
                                                  stepRouteModel.GetStepRouteName(),
                                                  subtitle,
                                                  iconKey,
                                               
                                                  Eegeo_NEW(SearchResultSection::View::SearchResultItemModel)(sTitleCategory,
                                                                                                              latlong.ToECEF(),
                                                                                                              stepRouteModel.GetInInterior(),
                                                                                                              true,
                                                                                                              isWayPoint,
                                                                                                              m_buildingId,
                                                                                                              stepRouteModel.GetLevel(),
                                                                                                              m_directionMenuViewModel,                                                                           m_searchResultPoiViewModel,
                                                                                                              m_wayPointCount,
                                                                                                              m_messageBus,
                                                                                                              m_menuReaction,wayPointNumber,wayPointype));
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
            
            ExampleApp::Search::SdkModel::TagIconKey DirectionResultSectionController::GetIconImageName(const Direction::SdkModel::StepRouteModel &stepManeuver)
            {
                ExampleApp::Search::SdkModel::TagIconKey iconKey = ""; //DirectionCard_ElevatorSelected
                if(stepManeuver.GetStepType() == "Entrance")
                {
                    iconKey = "DirectionCard_EnterMallSelected";
                }
                else if(stepManeuver.GetStepType() == "Elevator")
                {
                    iconKey = "DirectionCard_ElevatorStandard";
                }
                else if (stepManeuver.GetManeuverRouteModel().GetModifier() == "" && stepManeuver.GetManeuverRouteModel().GetType() == "depart")
                {
                    iconKey = "DirectionCard_RouteStart";

                }
                else if (stepManeuver.GetManeuverRouteModel().GetModifier() == "" && stepManeuver.GetManeuverRouteModel().GetType() == "arrive")
                {
                    iconKey = "DirectionCardWayPt_SetRouteEnd";
                }
                else if (stepManeuver.GetManeuverRouteModel().GetModifier() == "slight right")
                {
                    iconKey = "DirectionCard_VeerRight";

                }
                else if (stepManeuver.GetManeuverRouteModel().GetModifier() == "slight left")
                {
                    iconKey = "DirectionCard_VeerLeft";
                }
                else if (stepManeuver.GetManeuverRouteModel().GetModifier() == "right")
                {
                    iconKey = "DirectionCard_TurnRight";
 
                }
                else if (stepManeuver.GetManeuverRouteModel().GetModifier() == "left")
                {
                    iconKey = "DirectionCard_TurnLeft";

                }
                else if (stepManeuver.GetManeuverRouteModel().GetModifier() == "sharp right")
                {
                    iconKey = "DirectionCard_TurnSharpRight";
                }
                else if (stepManeuver.GetManeuverRouteModel().GetModifier() == "sharp left")
                {
                    iconKey = "DirectionCard_TurnSharpLeft";
                }
                else if (stepManeuver.GetManeuverRouteModel().GetModifier() == "straight")
                {
                    iconKey = "DirectionCard_StraightAhead";
                }
                return iconKey;
            }


        }
    }
}


