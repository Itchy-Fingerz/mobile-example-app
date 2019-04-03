// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "InteriorsExplorerExitMessage.h"
#include "InteractionModelStateChangedMessage.h"
#include "ICameraTransitionController.h"
#include <map>
#include "IVenueLabelsController.h"
#include "SearchMenuSearchWithContextMessage.h"
#include "SearchResultViewClearedMessage.h"
#include "SearchMenuPerformedSearchMessage.h"

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
                bool m_isSearchMode;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<VenueLabelsChangedObserver, const InteriorsExplorer::InteriorsExplorerExitMessage&> m_interiorsExplorerExitMessageHandler;
                Eegeo::Helpers::TCallback1<VenueLabelsChangedObserver, const InteriorsExplorer::InteractionModelStateChangedMessage&> m_InteractionModelStateChangedMessageHandler;
                Eegeo::Helpers::TCallback1<VenueLabelsChangedObserver, const SearchMenu::SearchMenuSearchWithContextMessage&> m_SearchMenuSearchWithContextMessageHandler;
                Eegeo::Helpers::TCallback1<VenueLabelsChangedObserver, const SearchResultSection::SearchResultViewClearedMessage&> m_SearchQueryResultsRemovedMessageHandler;
                Eegeo::Helpers::TCallback1<VenueLabelsChangedObserver, const SearchMenu::SearchMenuPerformedSearchMessage&> m_SearchMenuPerformedSearchMessageHandler;

            
                void OnInteriorsExplorerExitMessage(const InteriorsExplorer::InteriorsExplorerExitMessage &message);
                void OnInteractionModelStateChangedMessage(const InteriorsExplorer::InteractionModelStateChangedMessage &message);
                void OnSearchMenuSearchWithContextMessage(const SearchMenu::SearchMenuSearchWithContextMessage &message);
                void OnSearchQueryResultsRemovedMessage(const SearchResultSection::SearchResultViewClearedMessage &message);
                void OnSearchMenuPerformedSearchMessage(const SearchMenu::SearchMenuPerformedSearchMessage &message);
            
            public:
                VenueLabelsChangedObserver(IVenueLabelsController& venueLabelsController,ExampleAppMessaging::TMessageBus& messageBus);
                ~VenueLabelsChangedObserver();

            };
        }
    }
}
