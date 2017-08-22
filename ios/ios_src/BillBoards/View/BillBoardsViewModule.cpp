// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "Types.h"
#include "BillBoardsViewModule.h"


namespace ExampleApp
{
    namespace BillBoards
    {
        namespace View
        {
            BillBoardsViewModule::BillBoardsViewModule(ExampleApp::BillBoards::SdkModel::BillBoardsRepository& billBoardRepository,BillBoards::View::BillBoardService& billBoardServices,ExampleApp::VideoAssetReader::VideoAssetReaderService& videoAssetService, Search::SdkModel::ISearchService& searchService,Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel, ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pBillBoardsController = Eegeo_NEW(ExampleApp::BillBoards::SdkModel::BillBoardsController)(billBoardRepository,billBoardServices, videoAssetService, searchService, interiorInteractionModel);
            }
            
            BillBoardsViewModule::~BillBoardsViewModule()
            {
                Eegeo_DELETE(m_pBillBoardsController);
                
            }
        }
    }
}
