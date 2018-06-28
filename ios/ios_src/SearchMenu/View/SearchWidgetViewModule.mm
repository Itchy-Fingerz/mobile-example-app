#include "SearchWidgetViewModule.h"
#include "SearchResultsRepository.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetViewModule::SearchWidgetViewModule(
                                                           Modality::View::IModalBackgroundView& modalBackgroundView,
                                                           Menu::View::IMenuViewModel& viewModel,
                                                           bool isNavigationEnabled,
                                                           ExampleAppMessaging::TMessageBus& messageBus
                                                           )
            {
                m_pSearchProvider = Eegeo_NEW(SearchProviders::SearchProvider)();
                
                m_pWrldSearchProvider = [[WidgetSearchProvider alloc] initWithSearchProvider: m_pSearchProvider];
                
                
                
                m_pView = [[SearchWidgetContainerView alloc] initWithSearchProvider:m_pWrldSearchProvider
                                                                  navigationEnabled:isNavigationEnabled
                                                                messageBus:messageBus];
                
                m_pSearchResults = Eegeo_NEW(SearchResultsRepository)();
                m_pSuggestions = Eegeo_NEW(SearchResultsRepository)();
                
                m_pSearchServices = Eegeo_NEW(SearchMenu::View::SearchServices)(*m_pSearchProvider,
                                                                                *m_pSearchResults,
                                                                                *m_pSuggestions,
                                                                                messageBus);
                
                m_pSearchWidgetController = Eegeo_NEW(SearchWidgetController)(*[m_pView getInterop],
                                                                              *m_pSearchResults,
                                                                              modalBackgroundView,
                                                                              viewModel,
                                                                              messageBus);
            }
            
            SearchWidgetController& SearchWidgetViewModule::GetSearchWidgetController() const{
                return *m_pSearchWidgetController;
            }
            
            SearchWidgetContainerView& SearchWidgetViewModule::GetSearchWidgetView() const
            {
                return *m_pView;
            }
            
            ISearchResultsRepository& SearchWidgetViewModule::GetSuggestionsRepository() const
            {
                return *m_pSuggestions;
            }
            
            SearchWidgetViewModule::~SearchWidgetViewModule()
            {
                Eegeo_DELETE m_pSearchWidgetController;
                
                Eegeo_DELETE m_pSearchServices;
                
                Eegeo_DELETE m_pSuggestions;
                Eegeo_DELETE m_pSearchResults;
                
                [m_pView release];
                
                Eegeo_DELETE m_pSearchProvider;
            }
        }
        
    }
}

