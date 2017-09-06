// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsHighlightVisibilityController.h"
#include "ISearchService.h"
#include "ISearchQueryPerformer.h"
#include "ISearchResultRepository.h"
#include "InteriorInteractionModel.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "IInteriorsLabelController.h"
#include "VectorMath.h"
#include "InteriorHighlightRenderable.h"
#include "InteriorsLabelParser.h"
#include "InteriorsFloorCells.h"
#include "InteriorsFloorCell.h"
#include "PlaceNameModel.h"
#include "InteriorsCellResource.h"
#include "InteriorsCellResourceObserver.h"
#include "LabelAnchorFilterModel.h"
#include "IAnchoredLabel.h"
#include "document.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            namespace Highlights
            {
                InteriorsHighlightVisibilityController::InteriorsHighlightVisibilityController(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                                               Eegeo::Resources::Interiors::InteriorsCellResourceObserver& interiorsCellResourceObserver,
                                                                                               Search::SdkModel::ISearchService& searchService,
                                                                                               Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                                               Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                                                                               Eegeo::Resources::Interiors::Entities::IInteriorsLabelController& legacyLabelController,
                                                                                               Eegeo::Labels::ILabelAnchorFilterModel& labelHiddenFilterModel,
                                                                                               const Eegeo::Labels::LabelLayer::IdType interiorLabelLayer,
                                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                                               IHighlightColorMapper& highlightColorMapper)
                    : m_interiorInteractionModel(interiorInteractionModel)
                    , m_interiorsCellResourceObserver(interiorsCellResourceObserver)
                    , m_interiorLabelLayer(interiorLabelLayer)
                    , m_labelHiddenFilterModel(labelHiddenFilterModel)
                    , m_searchService(searchService)
                    , m_searchQueryPerformer(searchQueryPerformer)
                    , m_searchResultRepository(searchResultRepository)
                    , m_highlightColorMapper(highlightColorMapper)
                    , m_searchResultsHandler(this, &InteriorsHighlightVisibilityController::OnSearchResultsLoaded)
                    , m_searchResultsClearedHandler(this, &InteriorsHighlightVisibilityController::OnSearchResultCleared)
                    , m_interiorInteractionModelChangedHandler(this, &InteriorsHighlightVisibilityController::OnInteriorChanged)
                    , m_interiorCellAddedHandler(this, &InteriorsHighlightVisibilityController::OnInteriorAddedToSceneGraph)
                    , m_availabilityChangedHandlerBinding(this, &InteriorsHighlightVisibilityController::OnAvailabilityChanged)
                    , m_interiorLabelsBuiltHandler(this, &InteriorsHighlightVisibilityController::OnInteriorLabelsBuilt)
                    , m_hideLabelAlwaysFilter(this, &InteriorsHighlightVisibilityController::HideLabelAlwaysPredicate)
                    , m_billBoardSelectedHandler(this, &InteriorsHighlightVisibilityController::BillboardsSelected)
                    , m_showOfferMessageHandler(this, &InteriorsHighlightVisibilityController::ShowOffersSlected)
                    , m_isOffersActivated(false)
                    , m_messageBus (messageBus)
                    , m_hideLabelByNameFilter(this, &InteriorsHighlightVisibilityController::HideLabelByNamePredicate)
                    , m_isSearchResultsCleared(false)
                    , m_selectFloorCallback(this,&InteriorsHighlightVisibilityController::OnSelectFloor)

                
                {
                    m_searchService.InsertOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.InsertOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorInteractionModel.RegisterModelChangedCallback(m_interiorInteractionModelChangedHandler);
                    
                    m_messageBus.SubscribeNative(m_billBoardSelectedHandler);
                    m_messageBus.SubscribeNative(m_showOfferMessageHandler);
                    
                    m_messageBus.SubscribeNative(m_selectFloorCallback);
                    
                    m_interiorsCellResourceObserver.RegisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);

                    m_labelHiddenFilterModel.SetFilter(m_interiorLabelLayer, &m_hideLabelAlwaysFilter);
                    m_lastSelectedBillBoard = "";

                }

                InteriorsHighlightVisibilityController::~InteriorsHighlightVisibilityController()
                {
                    m_interiorsCellResourceObserver.UnregisterAddedToSceneGraphCallback(m_interiorCellAddedHandler);
                    
                    m_searchService.RemoveOnReceivedQueryResultsCallback(m_searchResultsHandler);
                    m_searchQueryPerformer.RemoveOnSearchResultsClearedCallback(m_searchResultsClearedHandler);
                    m_interiorInteractionModel.UnregisterModelChangedCallback(m_interiorInteractionModelChangedHandler);
                    
                    m_messageBus.UnsubscribeNative(m_billBoardSelectedHandler);
                    m_messageBus.UnsubscribeNative(m_showOfferMessageHandler);
                }

                void InteriorsHighlightVisibilityController::OnAvailabilityChanged()
                {
                }

                void InteriorsHighlightVisibilityController::DeactivateHighlightRenderables()
                {
                    const Eegeo::v4 transparent(1.0f, 1.0f, 1.0f, 0.0f);
                    
                    for (std::map<std::string, std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>>::iterator it = m_currentHighlightRenderables.begin();
                         it != m_currentHighlightRenderables.end();
                         ++it)
                    {
                        for (auto& renderable : it->second)
                        {
                            renderable->SetDiffuseColor(transparent);
                        }
                    }
                }
                
                void InteriorsHighlightVisibilityController::ActivateLabels(bool active)
                {
                    m_labelHiddenFilterModel.SetFilter(m_interiorLabelLayer, active ? NULL : &m_hideLabelByNameFilter);
                }


                void InteriorsHighlightVisibilityController::OnInteriorLabelsBuilt()
                {
                    ShowHighlightsForCurrentResults();
                    
                    bool hasResults = m_searchResultRepository.GetItemCount() > 0;
                    ActivateLabels(!hasResults);
                    
                }

                void InteriorsHighlightVisibilityController::OnSearchResultCleared()
                {
                    DeactivateHighlightRenderables();
                    ActivateLabels(true);
                    m_selectedBillBoards.clear();
                    m_isOffersActivated = false;
                    m_isSearchResultsCleared = true;
                    m_lastSelectedBillBoard = "";
                }

                void InteriorsHighlightVisibilityController::OnInteriorChanged()
                {
                    namespace EegeoInteriors = Eegeo::Resources::Interiors;
                    namespace EegeoRenderables = Eegeo::Rendering::Renderables;
                    
                    DeactivateHighlightRenderables();
                    m_currentHighlightRenderables.clear();
                    
                    if (m_interiorInteractionModel.HasInteriorModel())
                    {
                        const EegeoInteriors::InteriorsModel& model = *m_interiorInteractionModel.GetInteriorModel();
                        
                        for (EegeoInteriors::TFloorModelVector::const_iterator floors = model.GetFloors().begin();
                             floors != model.GetFloors().end();
                             ++floors)
                        {
                            const EegeoInteriors::InteriorsFloorCells* floorCells = model.GetFloorCells((*floors)->GetFloorNumber());
                            
                            for (int cellIndex = 0; cellIndex < floorCells->GetCellCount(); ++cellIndex)
                            {
                                const EegeoInteriors::InteriorsFloorCell* cell = floorCells->GetFloorCells()[cellIndex];
                                std::vector<EegeoRenderables::InteriorHighlightRenderable*> renderables = cell->GetHighlightRenderables();
                                
                                for (std::vector<EegeoRenderables::InteriorHighlightRenderable*>::iterator renderableIterator = renderables.begin();
                                     renderableIterator != renderables.end();
                                     ++renderableIterator)
                                {
                                    AddHighlight(**renderableIterator);
                                }
                            }
                        }
                        
                        if (m_currentHighlightRenderables.size() > 0)
                        {
                            ShowHighlightsForCurrentResults();
                        }
                        bool hasResults = m_searchResultRepository.GetItemCount() > 0;
                        ActivateLabels(!hasResults);
                    }
                    else
                    {
                        DeactivateHighlightRenderables();
                        m_currentHighlightRenderables.clear();
                        m_isSearchResultsCleared = false;
                    }
                }

                void InteriorsHighlightVisibilityController::OnInteriorAddedToSceneGraph(const Eegeo::Resources::Interiors::InteriorsCellResource& resource)
                {
                    if (m_interiorInteractionModel.HasInteriorModel())
                    {
                        const Eegeo::Resources::Interiors::InteriorsModel& model = *m_interiorInteractionModel.GetInteriorModel();
                        if (model.GetId() == resource.GetInteriorId())
                        {
                            OnInteriorChanged();
                        }
                    }
                }

                void InteriorsHighlightVisibilityController::AddHighlight(Eegeo::Rendering::Renderables::InteriorHighlightRenderable& renderable)
                {
                    static const std::string highlightPrefix = "entity_highlight ";
                    const std::string& id = renderable.GetRenderableId();

                    if (id.compare(0, highlightPrefix.length(), highlightPrefix) == 0)
                    {
                        std::string highlightId = id.substr(highlightPrefix.length());
                        if (m_currentHighlightRenderables.find(highlightId) == m_currentHighlightRenderables.end())
                        {
                            std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*> highlights;
                            m_currentHighlightRenderables.insert(std::make_pair(highlightId, highlights));
                        }
                        m_currentHighlightRenderables[highlightId].push_back(&renderable);
                    }
                }

                void InteriorsHighlightVisibilityController::OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    DeactivateHighlightRenderables();
                    
                    if (m_isOffersActivated)
                    {
                        
                        if(OnShowOffersFromResults(results))
                        {
                            ActivateLabels(false);
                        }
                        return;
                    }
                    
                    if(IsFullAdvertisementModeOn())
                    {
                        AddBillBoardToSelectedFromResults(m_lastSelectedBillBoard,results);
                        
                        ShowHighlightsForResults(m_selectedBillBoards);
                        
                        return;
                    }

                    ShowHighlightsForResults(results);

                    //bool hasResults = m_searchResultRepository.GetItemCount() > 0;
                    bool hasResults = results.size() > 0;
                    ActivateLabels(!hasResults);
                }

                bool InteriorsHighlightVisibilityController::ShowHighlightsForCurrentResults()
                {
                    if(IsFullAdvertisementModeOn())
                    {
                        ShowHighlightsForResults(m_selectedBillBoards);
                        
                        if(m_selectedBillBoards.size() > 0)
                        {
                            return true;
                        }
                        
                        return false;
                    }
                    std::vector<Search::SdkModel::SearchResultModel> results;
                    results.reserve(m_searchResultRepository.GetItemCount());

                    for (int i = 0; i < m_searchResultRepository.GetItemCount(); i++)
                    {
                        Search::SdkModel::SearchResultModel* pResult = m_searchResultRepository.GetItemAtIndex(i);
                        results.push_back(*pResult);
                    }

                    return ShowHighlightsForResults(results);
                }
                
                bool InteriorsHighlightVisibilityController::ShowHighlightsForResults(const std::vector<Search::SdkModel::SearchResultModel> &results)
                {
                    bool showingHighlights = false;
                    
                    if (m_interiorInteractionModel.HasInteriorModel() && m_currentHighlightRenderables.size() == 0)
                    {
                        OnInteriorChanged();
                    }
                    
                    rapidjson::Document json;
                    std::string highlightedRoomId = "";
                    
                    for (std::vector<Search::SdkModel::SearchResultModel>::const_iterator resultsItt = results.begin(); resultsItt != results.end(); ++resultsItt)
                    {
                        if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("highlight"))
                        {
                            highlightedRoomId = json["highlight"].GetString();
                            
                            for (std::map<std::string, std::vector<Eegeo::Rendering::Renderables::InteriorHighlightRenderable*>>::iterator renderItt = m_currentHighlightRenderables.begin();
                                 renderItt != m_currentHighlightRenderables.end();
                                 ++renderItt)
                            {
                                for (auto& renderable : renderItt->second)
                                {
                                    if (renderable->GetRenderableId().compare("entity_highlight " + highlightedRoomId) == 0)
                                    {
                                        renderable->SetDiffuseColor(m_highlightColorMapper.GetColor(*resultsItt, "highlight_color"));
                                        showingHighlights = true;
                                    }
                                }
                            }
                        }
                    }
                    
                    return showingHighlights;
                }
                
                bool InteriorsHighlightVisibilityController::HideLabelAlwaysPredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const
                {
                    return true;
                }
                
                bool InteriorsHighlightVisibilityController::HideLabelByNamePredicate(const Eegeo::Labels::IAnchoredLabel& anchoredLabel) const
                {
                    const std::string& labelCategoryName = anchoredLabel.GetLabelAnchorCategory().GetId();
                    bool shouldHide =  labelCategoryName != "interior_facility_escalator"
                    && labelCategoryName != "interior_facility_stairs"
                    && labelCategoryName != "interior_facility_elevator"
                    && labelCategoryName != "interior_facility_toilets";
                    return shouldHide;
                }

                
                void InteriorsHighlightVisibilityController::BillboardsSelected(const BillBoards::BillBoardSelectedMessage& selectedMessage)
                {
                    m_lastSelectedBillBoard = selectedMessage.GetPoiId();
                    
                    AddBillBoardToSelected(selectedMessage.GetPoiId());
                    
                    ShowHighlightsForResults(m_selectedBillBoards);

                    if(!IsFullAdvertisementModeOn() && !m_isOffersActivated)
                    {
                        m_messageBus.Publish(ExampleApp::SearchMenu::SearchMenuPerformedSearchMessage(selectedMessage.GetUniqueTag(), true, true));
                    }
                }
                
                void InteriorsHighlightVisibilityController::ShowOffersSlected(const BillBoards::ShowOfferHighlightMessage& selectedMessage)
                {
                    m_isOffersActivated = selectedMessage.GetSelectedOption();
                }
                
                bool InteriorsHighlightVisibilityController::OnShowOffersFromResults(const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    m_selectedBillBoards.clear();
                    for (int i = 0; i < results.size(); i++)
                    {
                        Search::SdkModel::SearchResultModel pResult = results.at(i);
                        
                        if(IsSpecialOfferBillBoard(&pResult))
                        {
                            if(!IsBillBoardAlreadySelected(pResult.GetIdentifier()))
                                m_selectedBillBoards.push_back(pResult);
                        }
                    }
                    m_isOffersActivated = true;
                    return ShowHighlightsForResults(m_selectedBillBoards);
                }
                
                bool InteriorsHighlightVisibilityController::OnHideOffers()
                {
                    bool isSpecialOffersLeft = true;
                    while(isSpecialOffersLeft)
                    {
                        isSpecialOffersLeft = false;
                        for (int i=0; i<m_selectedBillBoards.size();i++)
                        {
                            Search::SdkModel::SearchResultModel pResult = m_selectedBillBoards.at(i);
                            
                            if(IsSpecialOfferBillBoard(&pResult))
                            {
                                m_selectedBillBoards.erase(m_selectedBillBoards.begin() + i);
                                isSpecialOffersLeft = true;
                                break;
                            }
                        }
                    }
                    
                    OnInteriorChanged();
                    return true;
                }
                
                
                bool InteriorsHighlightVisibilityController::IsFullAdvertisementModeOn()
                {
                    return m_isSearchResultsCleared ? false : true;
                }
                
                void InteriorsHighlightVisibilityController::AddBillBoardToSelected(std::string poid)
                {
                    for (int i = 0; i < m_searchResultRepository.GetItemCount(); i++)
                    {
                        Search::SdkModel::SearchResultModel* pResult = m_searchResultRepository.GetItemAtIndex(i);
                        
                        if(pResult->GetIdentifier() == poid)
                        {
                            if(!IsBillBoardAlreadySelected(poid))
                                m_selectedBillBoards.push_back(*pResult);
                        }
                    }
                }
                
                void InteriorsHighlightVisibilityController::AddBillBoardToSelectedFromResults(std::string poid,const std::vector<Search::SdkModel::SearchResultModel>& results)
                {
                    for (int i = 0; i < results.size(); i++)
                    {
                       const Search::SdkModel::SearchResultModel pResult = results.at(i);
                        
                        if(pResult.GetIdentifier() == poid)
                        {
                            if(!IsBillBoardAlreadySelected(poid))
                                m_selectedBillBoards.push_back(pResult);
                        }
                    }
                }
                
                bool InteriorsHighlightVisibilityController::IsBillBoardAlreadySelected(std::string poid)
                {
                    for (int i = 0; i < m_selectedBillBoards.size(); i++)
                    {
                        Search::SdkModel::SearchResultModel pResult = m_selectedBillBoards.at(i);
                        
                        if(pResult.GetIdentifier() == poid)
                        {
                            return true;
                        }
                    }
                    return false;
                }

                bool InteriorsHighlightVisibilityController::IsSpecialOfferBillBoard(Search::SdkModel::SearchResultModel* pResult)
                {
                    for(int j = 0; j<pResult->GetTags().size();j++)
                    {
                        std::string tag = pResult->GetTags()[j];
                        if(tag == "offers")
                        {
                            return true;
                        }
                    }
                    
                    return false;
                }
                
                void InteriorsHighlightVisibilityController::OnSelectFloor(const InteriorsExplorer::InteriorsExplorerSelectFloorMessage &message)
                {
                    DeactivateHighlightRenderables();
                    ActivateLabels(true);
                    m_selectedBillBoards.clear();
//                    m_isOffersActivated = false;
                    m_lastSelectedBillBoard = "";
                }
            }
        }
    }
}
