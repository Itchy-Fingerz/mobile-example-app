// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorWorldPinController.h"
#include "InteriorSelectionModel.h"
#include "MenuDragStateChangedMessage.h"
#include "IInitialExperienceModel.h"
#include "InteriorSelectionController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorWorldPinController::InteriorWorldPinController(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                                   ExampleAppMessaging::TMessageBus& messageBus,
                                                                   const InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel,
                                                                   bool useIndoorEntryMarkerLabels)
            : m_interiorSelectionModel(interiorSelectionModel)
            , m_messageBus(messageBus)
            , m_menuDraggedCallback(this, &InteriorWorldPinController::HandleMenuDragged)
            , m_menuIsDragging(false)
            , m_initialExperienceModel(initialExperienceModel)
            , m_useIndoorEntryMarkerLabels(useIndoorEntryMarkerLabels)
            {
<<<<<<< HEAD
                if (!m_useIndoorEntryMarkerLabels)
                {
                    m_markerRepository.RegisterNotifyAddedCallback(m_markerAddedCallback);
                    m_markerRepository.RegisterNotifyRemovedCallback(m_markerRemovedCallback);
                }
                
=======
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
                m_messageBus.SubscribeNative(m_menuDraggedCallback);
            }
            
            InteriorWorldPinController::~InteriorWorldPinController()
            {
                m_messageBus.UnsubscribeNative(m_menuDraggedCallback);
<<<<<<< HEAD
                
                if (!m_useIndoorEntryMarkerLabels)
                {
                    m_markerRepository.UnregisterNotifyAddedCallback(m_markerAddedCallback);
                    m_markerRepository.UnregisterNotifyRemovedCallback(m_markerRemovedCallback);
                }
                
                for(std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*>::iterator it = m_interiorIdToWorldPinMap.begin();
                    it != m_interiorIdToWorldPinMap.end();
                    ++it)
                {
                    WorldPins::SdkModel::WorldPinItemModel* pPinModel = it->second;
                    m_worldPinsService.RemovePin(pPinModel);
                }
                
                m_interiorIdToWorldPinMap.clear();
=======
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
            }
            
            const bool InteriorWorldPinController::PinInteractionAllowed(const std::string& interiorId) const
            {
                const bool cameraUnlocked = m_initialExperienceModel.LockedCameraStepsCompleted();
                return !m_menuIsDragging && cameraUnlocked &&
<<<<<<< HEAD
                    !m_interiorSelectionModel.IsInteriorSelected() &&
                    m_deferedRemovalMap.find(interiorId) == m_deferedRemovalMap.end();
            }
            
            void InteriorWorldPinController::Update(float dt)
            {
                std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*>::iterator it;
                std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*>::iterator nextIt;
                for(it = m_deferedRemovalMap.begin(); it != m_deferedRemovalMap.end(); it = nextIt)
                {
                    nextIt = it;
                    ++nextIt;
                    m_worldPinsService.RemovePin(it->second);
                    m_interiorIdToWorldPinMap.erase(it->first);
                    m_deferedRemovalMap.erase(it);
                }
            }
            
            void InteriorWorldPinController::HandleMarkerAdded(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& markerModel)
            {
                if(m_deferedRemovalMap.erase(markerModel.GetInteriorId().Value()) != 0)
                {
                    return;
                }
                
                Eegeo_ASSERT(m_interiorIdToWorldPinMap.find(markerModel.GetInteriorId().Value()) == m_interiorIdToWorldPinMap.end(),
                             "InteriorWorldPinController already has a pin with that Id");
                
                const float heightOffsetMetres = 0.0f;
                const bool isInterior = false;
                const std::string indoorMapEntryIconKey = "indoor_map";
                WorldPins::SdkModel::WorldPinInteriorData worldPinInteriorData;
                
                ExampleApp::WorldPins::SdkModel::WorldPinFocusData worldPinFocusData(markerModel.GetInteriorName(),
                                                                                     markerModel.GetInteriorOwner(),
                                                                                     Search::InteriorVendorName);
                
                Eegeo::Space::LatLong location = Eegeo::Space::LatLong::FromDegrees(markerModel.GetMarkerLatLongAltitude().GetLatitudeInDegrees(),
                                                                                    markerModel.GetMarkerLatLongAltitude().GetLongitudeInDegrees());
                
                InteriorWorldPinSelectionHandler* pSelectionHandler = Eegeo_NEW(InteriorWorldPinSelectionHandler)(markerModel.GetInteriorId(),
                                                                                                                  m_interiorSelectionModel,
                                                                                                                  
                                                                                                                  *this);
                
                WorldPins::SdkModel::WorldPinItemModel* pItemModel = m_worldPinsService.AddPin(pSelectionHandler,
                                                                                               NULL,
                                                                                               worldPinFocusData,
                                                                                               isInterior,
                                                                                               worldPinInteriorData,
                                                                                               location,
                                                                                               indoorMapEntryIconKey,
                                                                                               heightOffsetMetres,
                                                                                               WorldPins::SdkModel::WorldPinVisibility::World);
                m_interiorIdToWorldPinMap[markerModel.GetInteriorId().Value()] = pItemModel;
            }
            
            void InteriorWorldPinController::HandleMarkerRemoved(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel &markerModel)
            {
                Eegeo_ASSERT(m_interiorIdToWorldPinMap.find(markerModel.GetInteriorId().Value()) != m_interiorIdToWorldPinMap.end(),
                             "InteriorWorldPinController does not have a pin with that Id");
                
                WorldPins::SdkModel::WorldPinItemModel* pPinModel = m_interiorIdToWorldPinMap[markerModel.GetInteriorId().Value()];
                
                m_deferedRemovalMap[markerModel.GetInteriorId().Value()] = pPinModel;
=======
                    !m_interiorSelectionModel.IsInteriorSelected();
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
            }
            
            void InteriorWorldPinController::HandleMenuDragged(const Menu::MenuDragStateChangedMessage &message)
            {
                m_menuIsDragging = message.IsDragging();
            }
        }
    }
}