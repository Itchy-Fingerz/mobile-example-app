// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "InteriorsExplorerExitMessage.h"
#include "InteractionModelStateChangedMessage.h"
#include "ICameraTransitionController.h"
#include <map>
#include "IVenueLabelsController.h"

namespace ExampleApp
{
    namespace VenueLabels
    {
        namespace SdkModel
        {
            class VenueLabelsChangedObserver
            {
            private:
            
                IVenueLabelsController& m_venueLabelsController;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<VenueLabelsChangedObserver, const InteriorsExplorer::InteriorsExplorerExitMessage&> m_interiorsExplorerExitMessageHandler;
                Eegeo::Helpers::TCallback1<VenueLabelsChangedObserver, const InteriorsExplorer::InteractionModelStateChangedMessage&> m_InteractionModelStateChangedMessageHandler;
            
                void OnInteriorsExplorerExitMessage(const InteriorsExplorer::InteriorsExplorerExitMessage &message);
                void OnInteractionModelStateChangedMessage(const InteriorsExplorer::InteractionModelStateChangedMessage &message);
            
            public:
                VenueLabelsChangedObserver(IVenueLabelsController& venueLabelsController,ExampleAppMessaging::TMessageBus& messageBus);
                ~VenueLabelsChangedObserver();

            };
        }
    }
}
