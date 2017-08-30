// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsEntityIdHighlightVisibilityController.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "ISearchResultRepository.h"
#include "InteriorController.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "IInteriorsLabelController.h"
#include "VectorMath.h"
#include "InteriorHighlightRenderable.h"
#include "InteriorsLabelParser.h"
#include "InteriorsFloorCells.h"
#include "InteriorsFloorCell.h"
#include "PlaceNameModel.h"
#include "InstancedInteriorFloorRenderable.h"
#include "InteriorsCellResource.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "InteriorsEntityIdHighlightController.h"
#include "document.h"

#include <algorithm>
#include <iterator>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                namespace
                {
                    std::vector<std::string> GetEntityIdsFromSearchResultModel(const Search::SdkModel::SearchResultModel& selectedSearchResult)
                    {
                        rapidjson::Document json;
                        std::string highlightedEntityId = "";
                        
                        if (!json.Parse<0>(selectedSearchResult.GetJsonData().c_str()).HasParseError() && json.HasMember("entity_highlight"))
                        {
                            std::vector<std::string> entities;
                            const rapidjson::Value& entity_highlight = json["entity_highlight"];
                            assert(entity_highlight.IsArray());
                            
                            for (int i  = 0; i < entity_highlight.Size(); i++)
                            {
                                entities.push_back(entity_highlight[i].GetString());
                            }
                            return entities;
                        }
                        return std::vector<std::string>();
                    }
                    
                    struct IsInteriorInstancePresentForId
                    {
                        typedef const std::string& argument_type;
                        
                        IsInteriorInstancePresentForId(const Eegeo::Resources::Interiors::InteriorsInstanceRepository& interiorsInstanceRepository)
                        : m_interiorsInstanceRepository(interiorsInstanceRepository)
                        {}
                        
                        bool operator()(argument_type id) const
                        {
                            return m_interiorsInstanceRepository.Contains(id);
                        }
                    private:
                        const Eegeo::Resources::Interiors::InteriorsInstanceRepository& m_interiorsInstanceRepository;
                    };
                }

                InteriorsEntityIdHighlightVisibilityController::InteriorsEntityIdHighlightVisibilityController(
                    Eegeo::Resources::Interiors::InteriorsEntityIdHighlightController& interiorsEntityIdHighlightController,
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    Search::SdkModel::ISearchResultRepository& searchResultRepository,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Eegeo::Resources::Interiors::InteriorsInstanceRepository& interiorsInstanceRepository,
                    IHighlightColorMapper& highlightColorMapper)
                : m_interiorsEntityIdHighlightController(interiorsEntityIdHighlightController)
                , m_searchQueryPerformer(searchQueryPerformer)
                , m_searchResultsHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded)
                , m_searchResultsClearedHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchResultsCleared)
                , m_handleSearchResultSectionItemSelectedMessageBinding(this, &InteriorsEntityIdHighlightVisibilityController::OnSearchItemSelected)
                , m_messageBus(messageBus)
                , m_interiorsInstanceRepository(interiorsInstanceRepository)
                , m_interiorsInstanceRepositoryChangedHandler(this, &InteriorsEntityIdHighlightVisibilityController::OnInteriorsInstanceRepositoryChanged)
                , m_searchResultsIndex(-1)
                , m_highlightColorMapper(highlightColorMapper)
                {
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_messageBus.SubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                    m_messageBus.SubscribeUi(m_searchResultsHandler);
                    
                    m_interiorsInstanceRepository.RegisterChangedCallback(m_interiorsInstanceRepositoryChangedHandler);
                }
                
                InteriorsEntityIdHighlightVisibilityController::~InteriorsEntityIdHighlightVisibilityController()
                {
                    m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_messageBus.UnsubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                    m_messageBus.UnsubscribeUi(m_searchResultsHandler);
                    
                    m_interiorsInstanceRepository.UnregisterChangedCallback(m_interiorsInstanceRepositoryChangedHandler);
                }
                
                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultsCleared()
                {
                    m_searchResultsIndex = -1;
                    m_searchResults.clear();
                    ClearHighlights();
                }

                void InteriorsEntityIdHighlightVisibilityController::ClearHighlights()
                {
                    m_interiorsEntityIdHighlightController.ClearHighlights(m_lastHighlightedRenderables);
                    m_lastHighlightedRenderables.clear();
                }

                void InteriorsEntityIdHighlightVisibilityController::OnSearchItemSelected(const SearchResultSection::SearchResultSectionItemSelectedMessage& message)
                {
                    if (message.ItemIndex() >= m_searchResults.size())
                    {
                        m_searchResultsIndex = -1;
                    }
                    else
                    {
                        m_searchResultsIndex = message.ItemIndex();
                    }
                    
                    RefreshHighlights();
                }
                
                void InteriorsEntityIdHighlightVisibilityController::OnInteriorsInstanceRepositoryChanged()
                {
                    RefreshHighlights();
                }


                void InteriorsEntityIdHighlightVisibilityController::OnSearchResultsLoaded(const Search::SearchQueryResponseReceivedMessage& message)
                {
                    if (m_searchResultsIndex >= 0)
                    {
                        const Search::SdkModel::SearchResultModel& selectedSearchResult = m_searchResults.at(m_searchResultsIndex);

                        const std::vector<Search::SdkModel::SearchResultModel>& newSearchResults = message.GetResults();

                        std::vector<Search::SdkModel::SearchResultModel>::const_iterator iter = std::find(newSearchResults.begin(), newSearchResults.end(), selectedSearchResult);
                        if (iter == newSearchResults.end())
                        {
                            m_searchResultsIndex = -1;                            
                        }
                        else
                        {
                            m_searchResultsIndex = static_cast<int>(std::distance(newSearchResults.begin(), iter));
                        }
                    }

                    m_searchResults = message.GetResults();

                    RefreshHighlights();
                }
                
                void InteriorsEntityIdHighlightVisibilityController::RefreshHighlights()
                {
                    ClearHighlights();

                    if (m_searchResultsIndex >= 0)
                    {
                        const Search::SdkModel::SearchResultModel& selectedSearchResult = m_searchResults.at(m_searchResultsIndex);

                        std::vector<std::string> filteredEntityIds = GetEntityIdsFromSearchResultModel(selectedSearchResult);
                        
                        filteredEntityIds.erase(std::remove_if(filteredEntityIds.begin(), filteredEntityIds.end(), std::not1(IsInteriorInstancePresentForId(m_interiorsInstanceRepository))), filteredEntityIds.end());

                        m_interiorsEntityIdHighlightController.SetDefaultHighlightColour(m_highlightColorMapper.GetColor(selectedSearchResult, "entity_highlight_color"));
                        m_interiorsEntityIdHighlightController.HighlightEntityIds(filteredEntityIds, m_lastHighlightedRenderables);
                    }
                }
            }
        }
    }
}
