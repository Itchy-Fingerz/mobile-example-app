// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsService.h"
#include "ILabelModelService.h"
#include "LatLongAltitude.h"
#include "IWorldPinsRepository.h"
#include "IInteriorMarkerPickingService.h"

#include "IMarkerService.h"
#include "MarkerBuilder.h"

#include <cstdlib>
#include <sstream>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            WorldPinsService::WorldPinsService(
                                               IWorldPinsRepository& worldPinsRepository,
                                               Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& interiorMarkerPickingService,
                                               Eegeo::Markers::IMarkerService& markerService,
                                               ExampleAppMessaging::TSdkModelDomainEventBus& sdkModelDomainEventBus,
                                               ExampleAppMessaging::TMessageBus& messageBus,
                                               Eegeo::Location::NavigationService& navigationService)
            : m_worldPinsRepository(worldPinsRepository)
            , m_interiorMarkerPickingService(interiorMarkerPickingService)
            , m_markerService(markerService)
            , m_sdkModelDomainEventBus(sdkModelDomainEventBus)
            , m_worldPinHiddenStateChangedMessageBinding(this, &WorldPinsService::OnWorldPinHiddenStateChanged)
            , m_onSearchResultSelected(this, &WorldPinsService::OnMenuItemSelected)
            , m_messageBus(messageBus)
            , m_navigationService(navigationService)
            {
                m_sdkModelDomainEventBus.Subscribe(m_worldPinHiddenStateChangedMessageBinding);
                m_messageBus.SubscribeNative(m_onSearchResultSelected);
            }
            
            WorldPinsService::~WorldPinsService()
            {
                m_messageBus.UnsubscribeNative(m_onSearchResultSelected);
                m_sdkModelDomainEventBus.Unsubscribe(m_worldPinHiddenStateChangedMessageBinding);
            }
            
            Eegeo::Markers::IMarker::IdType WorldPinsService::GetMarkerIdForWorldPinItemModelId(SdkModel::WorldPinItemModel::WorldPinItemModelId worldPinId) const
            {
                const Eegeo::Markers::IMarker::IdType markerId = worldPinId;
                return markerId;
            }
            
            WorldPinItemModel::WorldPinItemModelId WorldPinsService::GetWorldPinItemModelIdForMarkerId(Eegeo::Markers::IMarker::IdType markerId) const
            {
                const WorldPinItemModel::WorldPinItemModelId worldPinItemModelId = markerId;
                return worldPinItemModelId;
            }
            
            
            void WorldPinsService::OnWorldPinHiddenStateChanged(const WorldPinHiddenStateChangedMessage& message)
            {
                const SdkModel::WorldPinItemModel& worldPin = message.GetWorldPin();
                
                Eegeo::Markers::IMarker& marker = m_markerService.Get(GetMarkerIdForWorldPinItemModelId(worldPin.Id()));
                
                const bool isHidden = worldPin.IsHidden();
                marker.SetHidden(isHidden);
            }
            
            WorldPinItemModel* WorldPinsService::AddPin(IWorldPinSelectionHandler* pSelectionHandler,
                                                        IWorldPinVisibilityStateChangedHandler* pVisibilityStateChangedHandler,
                                                        const WorldPinFocusData& worldPinFocusData,
                                                        bool interior,
                                                        const WorldPinInteriorData& worldPinInteriorData,
                                                        const Eegeo::Space::LatLong& location,
                                                        const std::string& pinIconKey,
                                                        float heightAboveTerrainMetres,
                                                        int visibilityMask,
                                                        std::string identifier)
            {
                
                const auto& markerCreateParams = Eegeo::Markers::MarkerBuilder()
                .SetLocation(location.GetLatitudeInDegrees(), location.GetLongitudeInDegrees())
                .SetLabelText(worldPinFocusData.title)
                .SetLabelIcon(pinIconKey)
                // temp workaround to specify interior floor by zero-based index rather than 'floor number' id (MPLY-8062)
                .SetInteriorWithFloorIndex(worldPinInteriorData.building.Value(), worldPinInteriorData.floor)
                .SetSubPriority(worldPinFocusData.priorityOrder)
                .Build();
                
                const Eegeo::Markers::IMarker::IdType markerId = m_markerService.Create(markerCreateParams);
                const WorldPinItemModel::WorldPinItemModelId pinId = markerId;
                
                Eegeo_ASSERT(m_pinsToSelectionHandlers.find(pinId) == m_pinsToSelectionHandlers.end(), "Attempting to add same pin ID %d twice.\n", pinId);
                m_pinsToSelectionHandlers[pinId] = pSelectionHandler;
                
                Eegeo_ASSERT(m_pinsToVisbilityChangedHandlers.find(pinId) == m_pinsToVisbilityChangedHandlers.end(), "Attempting to add same pin ID %d twice.\n", pinId);
                m_pinsToVisbilityChangedHandlers[pinId] = pVisibilityStateChangedHandler;
                
                WorldPinItemModel* model = Eegeo_NEW(WorldPinItemModel)(pinId,
                                                                        pSelectionHandler,
                                                                        pVisibilityStateChangedHandler,
                                                                        worldPinFocusData,
                                                                        interior,
                                                                        worldPinInteriorData,
                                                                        visibilityMask,
                                                                        m_sdkModelDomainEventBus,
                                                                        identifier);
                
                m_worldPinsRepository.AddItem(model);
                
                return model;
            }
            
            void WorldPinsService::RemovePin(WorldPinItemModel* pPinItemModel)
            {
                const WorldPinItemModel::WorldPinItemModelId pinId = pPinItemModel->Id();
                
                const Eegeo::Markers::IMarker::IdType markerId = GetWorldPinItemModelIdForMarkerId(pinId);
                
                m_markerService.Destroy(markerId);
                
                IWorldPinSelectionHandler* pSelectionHandler = m_pinsToSelectionHandlers.at(pinId);
                m_pinsToSelectionHandlers.erase(pinId);
                Eegeo_DELETE pSelectionHandler;
                
                IWorldPinVisibilityStateChangedHandler* pVisibilityHandler = m_pinsToVisbilityChangedHandlers.at(pinId);
                m_pinsToVisbilityChangedHandlers.erase(pinId);
                Eegeo_DELETE pVisibilityHandler;
                
                m_worldPinsRepository.RemoveItem(pPinItemModel);
                Eegeo_DELETE pPinItemModel;
            }
            
            bool WorldPinsService::HandleTouchTap(const Eegeo::v2& screenTapPoint)
            {
                return TrySelectPinAtPoint(screenTapPoint);
            }
            
            bool WorldPinsService::HandleTouchDoubleTap(const Eegeo::v2& screenTapPoint)
            {
                return TrySelectPinAtPoint(screenTapPoint);
            }
            
            void WorldPinsService::SelectPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId)
            {
                IWorldPinSelectionHandler* selectionHandler = GetSelectionHandlerForPin(worldPinItemModelId);
                if(selectionHandler != NULL)
                {
                    selectionHandler->SelectPin();
                    ClearSelectedSearchResult();
                }
            }
            
            IWorldPinSelectionHandler* WorldPinsService::GetSelectionHandlerForPin(WorldPinItemModel::WorldPinItemModelId worldPinItemModelId)
            {
                if (m_pinsToSelectionHandlers.find(worldPinItemModelId) != m_pinsToSelectionHandlers.end())
                {
                    return m_pinsToSelectionHandlers[worldPinItemModelId];
                }
                else
                {
                    return NULL;
                }
            }
            
            bool WorldPinsService::TrySelectPinAtPoint(const Eegeo::v2& screenPoint)
            {
                if (m_interiorMarkerPickingService.TryEnterInterior(screenPoint))
                {
                    m_navigationService.SetGpsMode(Eegeo::Location::NavigationService::GpsMode::GpsModeOff);
                    return true;
                }
                
                auto pickedMarkerId = Eegeo::Markers::IMarker::InvalidId;
                if (m_markerService.TryPick(screenPoint, pickedMarkerId))
                {
                    const WorldPinItemModel::WorldPinItemModelId pinId = GetWorldPinItemModelIdForMarkerId(pickedMarkerId);
                    SelectPin(pinId);
                    return true;
                }
                
                return false;
            }
            
            WorldPinItemModel* WorldPinsService::FindWorldPinItemModelOrNull(const std::string& searchResultId) const
            {
                if (searchResultId.empty())
                {
                    return nullptr;
                }
                
                for (int i = 0; i < m_worldPinsRepository.GetItemCount(); i++)
                {
                    WorldPinItemModel* pWorldPinItemModel = m_worldPinsRepository.GetItemAtIndex(i);
                    if (pWorldPinItemModel->GetIdentifier() == searchResultId)
                    {
                        return pWorldPinItemModel;
                    }
                }
                
                return nullptr;
            }
            
            void WorldPinsService::OnMenuItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message)
            {
                ClearSelectedSearchResult();
                
                Eegeo_ASSERT(m_selectedSearchResultId.empty());
                
                m_selectedSearchResultId = message.ModelIdentifier();
                
                const WorldPinItemModel* pWorldPinItemModel = FindWorldPinItemModelOrNull(m_selectedSearchResultId);
                if (pWorldPinItemModel != nullptr)
                {
                    const auto& lastHighPriorityMarkerId = GetMarkerIdForWorldPinItemModelId(pWorldPinItemModel->Id());
                    Eegeo::Markers::IMarker& marker = m_markerService.Get(lastHighPriorityMarkerId);
                    
                    const int highPriorityDrawOrder = 0;
                    marker.SetSubPriority(highPriorityDrawOrder);
                }
            }
            
            void WorldPinsService::ClearSelectedSearchResult()
            {
                if (m_selectedSearchResultId.empty())
                {
                    return;
                }
                
                const WorldPinItemModel* pWorldPinItemModel = FindWorldPinItemModelOrNull(m_selectedSearchResultId);
                if (pWorldPinItemModel != nullptr)
                {
                    const auto& lastHighPriorityMarkerId = GetMarkerIdForWorldPinItemModelId(pWorldPinItemModel->Id());
                    
                    const int priorityOrder = pWorldPinItemModel->GetInFocusModel().GetPriorityOrder();
                    
                    Eegeo::Markers::IMarker& marker = m_markerService.Get(lastHighPriorityMarkerId);
                    marker.SetSubPriority(priorityOrder);
                }
                
                m_selectedSearchResultId.clear();
            }
        }
    }
}
