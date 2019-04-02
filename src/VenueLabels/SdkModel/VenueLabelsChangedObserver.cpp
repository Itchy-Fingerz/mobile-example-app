// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VenueLabelsChangedObserver.h"

namespace ExampleApp
{
    namespace VenueLabels
    {
        namespace SdkModel
        {
            VenueLabelsChangedObserver::VenueLabelsChangedObserver(IVenueLabelsController& venueLabelsController,ExampleAppMessaging::TMessageBus& messageBus)
            : m_venueLabelsController(venueLabelsController)
            , m_messageBus(messageBus)
            , m_interiorsExplorerExitMessageHandler(this,&VenueLabelsChangedObserver::OnInteriorsExplorerExitMessage)
            , m_InteractionModelStateChangedMessageHandler(this,&VenueLabelsChangedObserver::OnInteractionModelStateChangedMessage)
            {
                m_messageBus.SubscribeNative(m_interiorsExplorerExitMessageHandler);
                m_messageBus.SubscribeUi(m_InteractionModelStateChangedMessageHandler);
            }
        
            VenueLabelsChangedObserver::~VenueLabelsChangedObserver()
            {
                m_messageBus.UnsubscribeNative(m_interiorsExplorerExitMessageHandler);
                m_messageBus.UnsubscribeUi(m_InteractionModelStateChangedMessageHandler);
            }
        
            void VenueLabelsChangedObserver::OnInteriorsExplorerExitMessage(const InteriorsExplorer::InteriorsExplorerExitMessage &message)
            {
                m_venueLabelsController.ClearLabels();
            }
        
            void VenueLabelsChangedObserver::OnInteractionModelStateChangedMessage(const InteriorsExplorer::InteractionModelStateChangedMessage &message)
            {
                m_venueLabelsController.ResetLabels(message.GetSelectedFloorIndex());
            }
        }
    }
}

