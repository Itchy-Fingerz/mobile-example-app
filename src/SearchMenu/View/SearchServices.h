// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "ISearchProvider.h"
#include "SearchServicesResult.h"
#include "SearchResultModel.h"
#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "SearchQueryResponseReceivedMessage.h"
#include "AutocompleteSuggestionsReceivedMessage.h"
#include "ISearchResultsRepository.h"
#include <vector>

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			class SearchServices: private Eegeo::NonCopyable
			{
			private:
				ISearchProvider& m_searchProvider;
				ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<SearchServices, const std::string&> m_onSearchCallback;
				Eegeo::Helpers::TCallback1<SearchServices, const std::string&> m_onAutocompleteSuggestionsCallback;
				Eegeo::Helpers::TCallback2<SearchServices, const std::string&, const QueryContext&> m_onSearchWithContextCallback;
				Eegeo::Helpers::TCallback0<SearchServices> m_onCancelCallback;
				Eegeo::Helpers::TCallback1<SearchServices, const Search::SearchQueryResponseReceivedMessage&> m_responseReceivedHandler;
				Eegeo::Helpers::TCallback1<SearchServices, const Search::AutocompleteSuggestionsReceivedMessage&> m_autocompleteSuggestionsResponseReceivedHandler;

				ISearchResultsRepository& m_searchResultsRepository;
				ISearchResultsRepository& m_suggestionsRepository;

			public:
				SearchServices(ISearchProvider& searchProvider,
							   ISearchResultsRepository& searchResultsRepository,
							   ISearchResultsRepository& suggestionsRepository,
							   ExampleAppMessaging::TMessageBus& messageBus);
				~SearchServices();


			private:
				void OnSearch(const std::string& searchQuery);
				void OnSearchWithContext(const std::string& searchQuery, const QueryContext& context);
				void OnCancel();
				void OnAutocompleteSuggestions(const std::string& searchQuery);
				void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);
				void OnAutocompleteSuggestionsResponseReceivedMessage(const Search::AutocompleteSuggestionsReceivedMessage& message);
			};
		}
	}
}
