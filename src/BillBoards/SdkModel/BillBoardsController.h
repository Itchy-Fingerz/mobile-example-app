// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "BillBoards.h"
#include "BillBoardModel.h"
#include "BillBoardService.h"
#include "QuadLineFactory.h"
#include "VideoAssetReaderService.h"
#include "Search.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            class BillBoardsController
            {
            private:
                
                BillBoards::View::BillBoardService& m_billBoardService;
                ExampleApp::BillBoards::SdkModel::BillBoardsRepository& m_billBoardrepository;
                Eegeo::Helpers::TCallback1<BillBoardsController, ExampleApp::BillBoards::SdkModel::BillBoardModel*> m_billBoardAddedCallback;
                Eegeo::Helpers::TCallback1<BillBoardsController, ExampleApp::BillBoards::SdkModel::BillBoardModel*> m_billBoardRemoveCallback;

                ExampleApp::VideoAssetReader::VideoAssetReaderService& m_videoAssetReaderService;
                
                Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                
                void OnBillBoardAdded(ExampleApp::BillBoards::SdkModel::BillBoardModel*&);
                void OnBillBoardRemoved(ExampleApp::BillBoards::SdkModel::BillBoardModel*&);

                Search::SdkModel::ISearchService& m_searchService;
                
                Eegeo::Helpers::TCallback2<BillBoardsController, const Search::SdkModel::SearchQuery&, const std::vector<Search::SdkModel::SearchResultModel>&> m_searchResultsHandler;
                
                void OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results);
                
                void AddVideoFrame(const View::BillBoardConfig& config);
            public:
                
                BillBoardsController(ExampleApp::BillBoards::SdkModel::BillBoardsRepository& billBoardRepository, BillBoards::View::BillBoardService& billBoardServices, ExampleApp::VideoAssetReader::VideoAssetReaderService& videoAssetService, Search::SdkModel::ISearchService& searchService, Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);
                
                ~BillBoardsController();
                
                void Update(float dt);
            };
        }
    }
}
