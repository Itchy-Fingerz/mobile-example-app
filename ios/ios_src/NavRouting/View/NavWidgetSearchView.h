#pragma once

#import <UIKit/UIKit.h>
#include "WrldNav/WrldNav.h"
#include "WrldSearchWidget/WrldSearchWidget.h"
#include "NavWidgetViewIncludes.h"
#include "WidgetSearchProvider.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetSearchView
            {
            private:
                WRLDSearchWidgetView* m_pSearchWidgetView;
                UIView* m_pResultsView;
                WRLDSearchModel* m_pSearchModel;
                WRLDSuggestionProviderHandle* m_pSuggestionProviderHandle;
                WRLDSearchProviderHandle* m_pSearchProviderHandle;
                
                QueryEvent m_autocompleteCancelledEvent;
                QueryEvent m_autocompleteCompletedEvent;
                
                SearchbarTextChangedEvent m_searchSearchBarTextChangeEvent;
                
                UIView* m_pContainer;
                UIButton* m_pBackButton;
                
                UIView* m_pSearchHintContainer;
                UIImageView* m_pSearchHintIcon;
                UILabel* m_pSearchHintLabel;
                BOOL m_hasShownHint;
                
                CGFloat m_animationTimeInSeconds = 0.2f;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<NavWidgetSearchView, const Search::AutocompleteSuggestionsReceivedMessage&> m_autocompleteSuggestionsResponseReceivedHandler;
                Eegeo::Helpers::TCallback1<NavWidgetSearchView, const Search::SearchQueryResponseReceivedMessage&> m_responseReceivedHandler;
                BOOL m_hasShown;

                void (^m_willPopulateResultCell) (WRLDSearchResultTableViewCell*);
                
                void ShowSearchHint();
                void HideSearchHint();
                
            public:
                NavWidgetSearchView(WidgetSearchProvider* navLocationFinder,ExampleAppMessaging::TMessageBus& messageBus_);
                
                ~NavWidgetSearchView();
                
                UIView* GetUIView();
                
                void Show();
                void Hide();
                
                void AddCloseButtonTarget(id target, SEL selector);
                void RemoveCloseButtonTarget(id target, SEL selector);
                void AddSelectedResultCallback(ResultSelectedEvent resultSelectedEvent);
                void RemoveSelectedResultCallback(ResultSelectedEvent resultSelectedEvent);
                
                void OnAutocompleteSuggestionsResponseReceivedMessage(const Search::AutocompleteSuggestionsReceivedMessage& message);
                void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);
            };
        }
    }
}
