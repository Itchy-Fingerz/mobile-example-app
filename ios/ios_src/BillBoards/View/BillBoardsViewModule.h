// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BillBoards.h"
#include "BillBoardService.h"
#include "BillBoardInteriorStateChangedObserver.h"
#include "BillBoardsController.h"
#include "VideoAssetReaderService.h"
#include "Search.h"



namespace ExampleApp
{
    namespace BillBoards
    {
        namespace View
        {
            class BillBoardsViewModule
            {
            private:
                ExampleApp::BillBoards::SdkModel::BillBoardsController* m_pBillBoardsController;
                
            public:
                BillBoardsViewModule(ExampleApp::BillBoards::SdkModel::BillBoardsRepository& billBoardRepository,BillBoards::View::BillBoardService& billBoardServices,ExampleApp::VideoAssetReader::VideoAssetReaderService& videoAssetService, Search::SdkModel::ISearchService& searchService,  ExampleAppMessaging::TMessageBus& messageBus);
                ~BillBoardsViewModule();
                        
            };
        }
    }
}
