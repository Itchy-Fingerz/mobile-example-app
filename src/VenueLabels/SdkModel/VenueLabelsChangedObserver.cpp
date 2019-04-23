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
            , m_SearchMenuSearchWithContextMessageHandler(this,&VenueLabelsChangedObserver::OnSearchMenuSearchWithContextMessage)
            , m_SearchQueryResultsRemovedMessageHandler(this,&VenueLabelsChangedObserver::OnSearchQueryResultsRemovedMessage)
            , m_SearchMenuPerformedSearchMessageHandler(this,&VenueLabelsChangedObserver::OnSearchMenuPerformedSearchMessage)
            , m_isSearchMode(false)
            {
                m_messageBus.SubscribeNative(m_interiorsExplorerExitMessageHandler);
                m_messageBus.SubscribeNative(m_SearchMenuSearchWithContextMessageHandler);
                m_messageBus.SubscribeNative(m_SearchMenuPerformedSearchMessageHandler);
                m_messageBus.SubscribeNative(m_SearchQueryResultsRemovedMessageHandler);
                m_messageBus.SubscribeUi(m_InteractionModelStateChangedMessageHandler);
            }
        
            VenueLabelsChangedObserver::~VenueLabelsChangedObserver()
            {
                m_messageBus.UnsubscribeNative(m_interiorsExplorerExitMessageHandler);
                m_messageBus.UnsubscribeNative(m_SearchMenuSearchWithContextMessageHandler);
                m_messageBus.UnsubscribeNative(m_SearchMenuPerformedSearchMessageHandler);
                m_messageBus.UnsubscribeNative(m_SearchQueryResultsRemovedMessageHandler);
                m_messageBus.UnsubscribeUi(m_InteractionModelStateChangedMessageHandler);
            }
        
            void VenueLabelsChangedObserver::OnInteriorsExplorerExitMessage(const InteriorsExplorer::InteriorsExplorerExitMessage &message)
            {
                m_venueLabelsController.ShowLabels(false);
            }
        
            void VenueLabelsChangedObserver::OnInteractionModelStateChangedMessage(const InteriorsExplorer::InteractionModelStateChangedMessage &message)
            {
                if (!m_isSearchMode && message.IsInteriorVisible())
                {
                    m_venueLabelsController.AddVenueLabels();
                    m_venueLabelsController.ShowLabels(true);
                }
            }
            
            void VenueLabelsChangedObserver::OnSearchMenuSearchWithContextMessage(const SearchMenu::SearchMenuSearchWithContextMessage &message)
            {
                m_venueLabelsController.ShowLabels(false);
                m_isSearchMode = true;
            }
            
            void VenueLabelsChangedObserver::OnSearchQueryResultsRemovedMessage(const SearchResultSection::SearchResultViewClearedMessage &message)
            {
                m_isSearchMode = false;
                m_venueLabelsController.ShowLabels(true);
            }
            
            void VenueLabelsChangedObserver::OnSearchMenuPerformedSearchMessage(const SearchMenu::SearchMenuPerformedSearchMessage &message)
            {
                m_venueLabelsController.ShowLabels(false);
                m_isSearchMode = true;
            }
        }
    }
}

