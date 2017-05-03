// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Search.h"
#include "Interiors.h"
#include "InteriorsExplorer.h"
#include "Rendering.h"
#include "BidirectionalBus.h"
#include "ILabelAnchorFilter.h"
#include "HighlightColorMapper.h"

#include <string>
#include <vector>
#include <map>

#include "BillBoardSelectedMessage.h"
#include "ShowOfferHighlightMessage.h"


namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                
                class InteriorsHighlightVisibilityController : protected Eegeo::NonCopyable
                {
                public:
                    InteriorsHighlightVisibilityController(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                           Eegeo::Resources::Interiors::InteriorsCellResourceObserver& interiorsCellResourceObserver,
                                                           Search::SdkModel::ISearchService& searchService,
                                                           Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                           Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                           Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& legacyLabelController,
                                                           Eegeo::Labels::ILabelAnchorFilterModel& labelHiddenFilterModel,
                                                           const Eegeo::Labels::LabelLayer::IdType interiorLabelLayer,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           IHighlightColorMapper& highlightColorMapper);
                    
                    ~InteriorsHighlightVisibilityController();
                    
                private:
                    void OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);
                    void OnSearchResultCleared();
                    
                    void OnInteriorChanged();
                    void OnInteriorAddedToSceneGraph(const Eegeo::Resources::Interiors::InteriorsCellResource& callback);
                    void OnInteriorLabelsBuilt();
                    void OnAvailabilityChanged();
                    
                    void DeactivateHighlightRenderables();
                    void AddHighlight(Eegeo::Rendering::Renderables::InteriorHighlightRenderable& renderable);
                    
                    bool ShowHighlightsForResults(const std::vector<Search::SdkModel::SearchResultModel>& results);
                    bool ShowHighlightsForCurrentResults();
                    void ActivateLabels(bool active);

                    void BillboardsSelected(const BillBoards::BillBoardSelectedMessage& selectedMessage);
                    void ShowOffersSlected(const BillBoards::ShowOfferHighlightMessage& selectedMessage);
                    bool OnShowOffers();
                    
                    bool HideLabelAlwaysPredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const;
                    bool HideLabelByNamePredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const;
                    
                    bool IsAdvertisementModeOn();
                    
                    bool IsBillBoardAlreadySelected(std::string poid);
                    
                    Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                    Eegeo::Resources::Interiors::InteriorsCellResourceObserver& m_interiorsCellResourceObserver;

                    Eegeo::Labels::ILabelAnchorFilterModel& m_labelHiddenFilterModel;
                    const Eegeo::Labels::LabelLayer::IdType m_interiorLabelLayer;
                    Search::SdkModel::ISearchService& m_searchService;
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    Search::SdkModel::ISearchResultRepository& m_searchResultRepository;
                    IHighlightColorMapper& m_highlightColorMapper;
                    
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    bool m_isOffersActivated;
                    
                    Eegeo::Helpers::TCallback1<InteriorsHighlightVisibilityController, const BillBoards::BillBoardSelectedMessage&> m_billBoardSelectedHandler;
                    Eegeo::Helpers::TCallback1<InteriorsHighlightVisibilityController, const BillBoards::ShowOfferHighlightMessage&> m_showOfferMessageHandler;
                    
                    Eegeo::Helpers::TCallback2<InteriorsHighlightVisibilityController, const Search::SdkModel::SearchQuery&, const std::vector<Search::SdkModel::SearchResultModel>&> m_searchResultsHandler;
                    Eegeo::Helpers::TCallback1<InteriorsHighlightVisibilityController, const Eegeo::Resources::Interiors::InteriorsCellResource> m_interiorCellAddedHandler;
                    Eegeo::Helpers::TCallback0<InteriorsHighlightVisibilityController> m_searchResultsClearedHandler;
                    Eegeo::Helpers::TCallback0<InteriorsHighlightVisibilityController> m_interiorInteractionModelChangedHandler;
                    Eegeo::Helpers::TCallback0<InteriorsHighlightVisibilityController> m_interiorLabelsBuiltHandler;
                    
                    Eegeo::Helpers::TCallback0<InteriorsHighlightVisibilityController> m_availabilityChangedHandlerBinding;
                    
                    std::map<std::string, std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>> m_currentHighlightRenderables;
                    
                    Eegeo::Labels::TLabelAnchorFilter<InteriorsHighlightVisibilityController> m_hideLabelAlwaysFilter;
                    Eegeo::Labels::TLabelAnchorFilter<InteriorsHighlightVisibilityController> m_hideLabelByNameFilter;
                    
                    std::vector<Search::SdkModel::SearchResultModel> m_selectedBillBoards;

                };
            }
        }
    }
}

