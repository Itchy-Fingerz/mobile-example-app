// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPointOnMapModel.h"
#include "WorldPinFocusData.h"
#include "WorldPinVisibility.h"
#include "IWorldPinsService.h"
#include "WayPointSelectionHandler.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {
            
            WayPointOnMapModel::WayPointOnMapModel(WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                   TagSearch::ISearchResultIconKeyMapper& searchResultIconCategoryMapper,
                                                   PathDrawing::SdkModel::IWayPointsRepository& wayPointsRepository,
                                                   ExampleAppMessaging::TMessageBus& messageBus,
                                                   ExampleApp::CameraTransitions::SdkModel::CameraTransitionService& cameraTransitionService)
            : m_onWayPointAddedCallBack(this, &WayPointOnMapModel::OnWayPointAdded)
            , m_onWayPointRemovedCallBack(this, &WayPointOnMapModel::OnWayPointRemoved)
            , m_worldPinsService(worldPinsService)
            , m_wayPointsRepository(wayPointsRepository)
            , m_messageBus(messageBus)
            , m_cameraTransitionService(cameraTransitionService)
            {
                wayPointsRepository.InsertItemAddedCallback(m_onWayPointAddedCallBack);
                wayPointsRepository.InsertItemRemovedCallback(m_onWayPointRemovedCallBack);
            }
            
            WayPointOnMapModel::~WayPointOnMapModel()
            {
                m_wayPointsRepository.RemoveItemAddedCallback(m_onWayPointAddedCallBack);
                m_wayPointsRepository.RemoveItemRemovedCallback(m_onWayPointRemovedCallBack);
            }
            
            void WayPointOnMapModel::OnWayPointAdded(WayPointModel*& wayPoint)
            {
                AddWayPointView(wayPoint);
            }
            
            void WayPointOnMapModel::AddWayPointView(WayPointModel*& wayPoint)
            {

                if(wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Start || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::End || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Left || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Right || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Elevator || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Entrance || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Escalator)
                {
                
                    WorldPins::SdkModel::WorldPinFocusData worldPinFocusData("",
                                                                             "",
                                                                             "",
                                                                             "",
                                                                             "",
                                                                             0,
                                                                             0);
                    
                    WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData(Eegeo::Resources::Interiors::InteriorId(wayPoint->GetBuildingID()), wayPoint->GetLevel());
                    
                    ExampleApp::WorldPins::SdkModel::WorldPinItemModel *pinItemModel =
                    m_worldPinsService.AddPin(Eegeo_NEW(WayPointSelectionHandler(*wayPoint,m_messageBus,m_cameraTransitionService))
                                              , NULL
                                              , worldPinFocusData
                                              , wayPoint->GetInInterior()
                                              , worldPinInteriorData
                                              , wayPoint->GetLocation()
                                              , GetWayPointIconForType(wayPoint->GetWayPointNumber())
                                              , 0.f
                                              , WorldPins::SdkModel::WorldPinVisibility::World);
                    
                    pinItemModel->SetFocusable(false);
                    m_wayPointsToPinModel.insert(std::make_pair(wayPoint, pinItemModel));
                }

            }
            
            void WayPointOnMapModel::OnWayPointRemoved(WayPointModel*& wayPoint)
            {
                RemoveWayPointView(wayPoint);
            }
            
            void WayPointOnMapModel::RemoveWayPointView(WayPointModel*& wayPoint)
            {

                if(wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Start || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::End || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Left || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Right || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Elevator || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Entrance )
                {
                    mapIt it = m_wayPointsToPinModel.find(wayPoint);
                
                    Eegeo_ASSERT(it != m_wayPointsToPinModel.end(),
                             "Trying to remove the world pin for a search result, but no pin exists for result.");
                
                    ExampleApp::WorldPins::SdkModel::WorldPinItemModel* pinItemModel = it->second;
                    m_worldPinsService.RemovePin(pinItemModel);
                    m_wayPointsToPinModel.erase(it);
                }
            }
            
            std::string WayPointOnMapModel::GetWayPointIconForType(int wayPointId)
            {
                switch (wayPointId) {
                    case 21:
                    {
                        return "dir_route_start";
                        break;
                    }
                    case 22:
                    {
                        return "dir_route_end";
                        break;
                    }
                    case 23:
                    {
                        return "dir_enter_map";
                        break;
                    }
                    case 24:
                    {
                        return "dir_elevator";
                        break;
                    }
                    case 25:
                    {
                        return "escalator";
                        break;
                    }
                    default:
                    {
                        return std::to_string(wayPointId);
                        break;
                    }
                }
                
            }
            
            void WayPointOnMapModel::HideAllWayPoints()
            {
                for (WayPointModelToPinMap::iterator it = m_wayPointsToPinModel.begin(); it != m_wayPointsToPinModel.end(); ++it)
                {
                    ExampleApp::WorldPins::SdkModel::WorldPinItemModel* pinItemModel = it->second;
                    m_worldPinsService.RemovePin(pinItemModel);
                }
            }
            
            void WayPointOnMapModel::ShowAllWayPoints()
            {
                for (WayPointModelToPinMap::iterator it = m_wayPointsToPinModel.begin(); it != m_wayPointsToPinModel.end(); ++it)
                {
                    WayPointModel *wayPoint = it->first;
                    
                    if(wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Start || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::End || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Left || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Right || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Elevator || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Entrance )
                    {
                        
                        WorldPins::SdkModel::WorldPinFocusData worldPinFocusData("",
                                                                                 "",
                                                                                 "",
                                                                                 "",
                                                                                 "",
                                                                                 0,
                                                                                 0);
                        
                        WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData(Eegeo::Resources::Interiors::InteriorId(wayPoint->GetBuildingID()), wayPoint->GetLevel());
                        
                        ExampleApp::WorldPins::SdkModel::WorldPinItemModel *pinItemModel =
                        m_worldPinsService.AddPin(Eegeo_NEW(WayPointSelectionHandler(*wayPoint,m_messageBus,m_cameraTransitionService))
                                                  , NULL
                                                  , worldPinFocusData
                                                  , wayPoint->GetInInterior()
                                                  , worldPinInteriorData
                                                  , wayPoint->GetLocation()
                                                  , GetWayPointIconForType(wayPoint->GetWayPointNumber())
                                                  , 0.f
                                                  , WorldPins::SdkModel::WorldPinVisibility::World);
                        
                        pinItemModel->SetFocusable(false);
                        it->second = pinItemModel;
                    }
                }
            }
        }
    }
}
