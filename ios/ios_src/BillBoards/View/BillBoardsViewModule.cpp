// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "Types.h"
#include "BillBoardsViewModule.h"


namespace ExampleApp
{
    namespace BillBoards
    {
        namespace View
        {
            BillBoardsViewModule::BillBoardsViewModule(ExampleApp::BillBoards::SdkModel::BillBoardsRepository& billBoardRepository,BillBoards::View::BillBoardService& billBoardServices,ExampleApp::VideoAssetReader::VideoAssetReaderService& videoAssetService, Search::SdkModel::ISearchService& searchService, ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pBillBoardsController = Eegeo_NEW(ExampleApp::BillBoards::SdkModel::BillBoardsController)(billBoardRepository,billBoardServices, videoAssetService, searchService);
                m_pBillBoardsController->CreateMockBillBoards();
                
                m_pChangeBillBoardsObserver = [[ChangeBillBoardObserver alloc] init:m_pBillBoardsController];
            }
            
            BillBoardsViewModule::~BillBoardsViewModule()
            {
                Eegeo_DELETE(m_pBillBoardsController);
                
                [m_pChangeBillBoardsObserver release];
                m_pChangeBillBoardsObserver = nil;
            }
        }
    }
}
