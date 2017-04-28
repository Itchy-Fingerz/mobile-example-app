// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IWorldPinsModule.h"
#include "WorldPins.h"
#include "Rendering.h"
#include "Camera.h"
#include "BidirectionalBus.h"
#include "IIdentity.h"
#include "IScreenControlViewModel.h"
#include "WorldPinsModalityObserver.h"
#include "Interiors.h"
#include "SdkModelDomainEventBus.h"
#include "Markers.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsModule : public IWorldPinsModule
            {
                IWorldPinsFactory* m_pWorldPinsFactory;
                IWorldPinsService* m_pWorldPinsService;
                IWorldPinsRepository* m_pWorldPinsRepository;
                IWorldPinsVisibilityController* m_pWorldPinsVisibilityController;
                WorldPinsModalityObserver* m_pWorldPinsModalityObserver;

            public:
                WorldPinsModule(ExampleAppMessaging::TMessageBus& messageBus,
                                const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                ExampleAppMessaging::TSdkModelDomainEventBus& sdkDomainEventBus,
                                Eegeo::Resources::Interiors::Markers::IInteriorMarkerPickingService& interiorMarkerPickingService,
                                Eegeo::Markers::IMarkerService& markerService
                                );

                ~WorldPinsModule();
                
                IWorldPinsRepository& GetWorldPinsRepository() const;
                
                void Update(float dt);

                IWorldPinsService& GetWorldPinsService() const;

                IWorldPinsFactory& GetWorldPinsFactory() const;

                IWorldPinsVisibilityController& GetWorldPinsVisibilityController() const;
            };
        }
    }
}

