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
                                                   ExampleAppMessaging::TMessageBus& messageBus)
            : m_onWayPointAddedCallBack(this, &WayPointOnMapModel::OnWayPointAdded)
            , m_onWayPointRemovedCallBack(this, &WayPointOnMapModel::OnWayPointRemoved)
            , m_worldPinsService(worldPinsService)
            , m_wayPointsRepository(wayPointsRepository)
            , m_messageBus(messageBus)
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
                if(wayPoint->GetIsWayPoint() == false)
                {
                    return;
                }
                if(wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Start || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::End || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Left || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Right || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Elevator || wayPoint->GetType() == ExampleApp::PathDrawing::WayPointType::Entrance )
                {
                
                    WorldPins::SdkModel::WorldPinFocusData worldPinFocusData("",
                                                                             "",
                                                                             "",
                                                                             "",
                                                                             "",
                                                                             0);
                    
                    WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData(Eegeo::Resources::Interiors::InteriorId(wayPoint->GetBuildingID()), wayPoint->GetLevel());
                    
                    ExampleApp::WorldPins::SdkModel::WorldPinItemModel *pinItemModel =
                    m_worldPinsService.AddPin(Eegeo_NEW(WayPointSelectionHandler(*wayPoint,m_messageBus))
                                              , NULL
                                              , worldPinFocusData
                                              , wayPoint->GetInInterior()
                                              , worldPinInteriorData
                                              , wayPoint->GetLocation()
                                              , GetWayPointIconForType(wayPoint->GetWayPointNumber())
                                              , 0.f
                                              , WorldPins::SdkModel::WorldPinVisibility::World);
                    
                    pinItemModel->SetFocusable(false);
                    // Add pin to map
                    
                    m_wayPointsToPinModel.insert(std::make_pair(wayPoint, pinItemModel));
                }

            }
            
            void WayPointOnMapModel::OnWayPointRemoved(WayPointModel*& wayPoint)
            {
                RemoveWayPointView(wayPoint);
            }
            
            void WayPointOnMapModel::RemoveWayPointView(WayPointModel*& wayPoint)
            {
                if(wayPoint->GetIsWayPoint() == false)
                {
                    return;
                }
                mapIt it = m_wayPointsToPinModel.find(wayPoint);
                
                Eegeo_ASSERT(it != m_wayPointsToPinModel.end(),
                             "Trying to remove the world pin for a search result, but no pin exists for result.");
                
                ExampleApp::WorldPins::SdkModel::WorldPinItemModel* pinItemModel = it->second;
                m_worldPinsService.RemovePin(pinItemModel);
                m_wayPointsToPinModel.erase(it);
            }
            
            std::string WayPointOnMapModel::GetWayPointIconForType(int wayPointId)
            {
                return std::to_string(wayPointId);
            }
        }
    }
}
