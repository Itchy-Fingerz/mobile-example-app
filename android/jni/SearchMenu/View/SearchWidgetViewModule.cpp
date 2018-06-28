// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchWidgetViewModule.h"
#include "SearchWidgetView.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "SearchResultsRepository.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			SearchWidgetViewModule::SearchWidgetViewModule(
				AndroidNativeState& nativeState,
				Modality::View::IModalBackgroundView& modalBackgroundView,
                Menu::View::IMenuViewModel& viewModel,
				bool showNavigationButtons,
				ExampleAppMessaging::TMessageBus& messageBus
			)
			{
				ASSERT_UI_THREAD

				m_pMyTestSearchProvider = Eegeo_NEW(SearchProviders::MyTestSearchProvider)(
						nativeState,
						showNavigationButtons
						);

				m_pSearchResults = Eegeo_NEW(SearchResultsRepository)();
				m_pSuggestions = Eegeo_NEW(SearchResultsRepository)();

				m_pSearchServices = Eegeo_NEW(SearchServices)(
						*m_pMyTestSearchProvider,
						*m_pSearchResults,
						*m_pSuggestions,
						messageBus);

				m_pSearchWidgetView = Eegeo_NEW(SearchWidgetView)(
						nativeState,
						*m_pMyTestSearchProvider);

				m_pSearchWidgetController = Eegeo_NEW(SearchWidgetController)(
						*m_pSearchWidgetView,
						*m_pSearchResults,
						modalBackgroundView,
                        viewModel,
						messageBus);
			}

			SearchWidgetController& SearchWidgetViewModule::GetSearchWidgetController() const
			{
				ASSERT_UI_THREAD

				return *m_pSearchWidgetController;
			}

			SearchProviders::MyTestSearchProvider& SearchWidgetViewModule::GetSearchProvider() const
			{
				return *m_pMyTestSearchProvider;
			}

			ISearchResultsRepository& SearchWidgetViewModule::GetSuggestionsRepository() const
			{
				return *m_pSuggestions;
			}

			SearchWidgetViewModule::~SearchWidgetViewModule()
			{
				ASSERT_UI_THREAD
				Eegeo_DELETE m_pSearchWidgetController;
				Eegeo_DELETE m_pSearchWidgetView;
                Eegeo_DELETE m_pSuggestions;
                Eegeo_DELETE m_pSearchResults;
				Eegeo_DELETE m_pSearchServices;
				Eegeo_DELETE m_pMyTestSearchProvider;

			}
		}

    }
}
