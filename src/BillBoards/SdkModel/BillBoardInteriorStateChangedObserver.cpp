// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardInteriorStateChangedObserver.h"
#include "SearchMenuPerformedSearchMessage.h"
#include "SetCustomAlertVisibilityMessage.h"
#include "InteriorSelectionModel.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            BillBoardInteriorStateChangedObserver::BillBoardInteriorStateChangedObserver(ExampleAppMessaging::TMessageBus& messageBus
                 ,View::BillBoardService& billBoardService,
                Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule)
            : m_selectFloorCallback(this,&BillBoardInteriorStateChangedObserver::OnSelectFloor)
            , m_exitInteriorCallback(this,&BillBoardInteriorStateChangedObserver::OnInteriorExit)
            , m_draggedFloorCallback(this,&BillBoardInteriorStateChangedObserver::OnDraggedFloor)
            , m_messageBus(messageBus)
            , m_billBoardService(billBoardService)
            , m_appModeChangedCallback(this, &BillBoardInteriorStateChangedObserver::OnAppModeChanged)
            , m_interiorsPresentationModule(interiorsPresentationModule)
            {
                m_messageBus.SubscribeNative(m_selectFloorCallback);
                m_messageBus.SubscribeNative(m_exitInteriorCallback);
                m_messageBus.SubscribeNative(m_draggedFloorCallback);
                m_messageBus.SubscribeUi(m_appModeChangedCallback);

            }
            
            BillBoardInteriorStateChangedObserver::~BillBoardInteriorStateChangedObserver()
            {
                m_messageBus.UnsubscribeNative(m_selectFloorCallback);
                m_messageBus.UnsubscribeNative(m_exitInteriorCallback);
                m_messageBus.UnsubscribeNative(m_draggedFloorCallback);
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
            }
            
            void BillBoardInteriorStateChangedObserver::OnSelectFloor(const InteriorsExplorer::InteriorsExplorerSelectFloorMessage &message)
            {
                m_billBoardService.RemoveAllRenderables();
                m_billBoardService.StopResetVideoService();
                m_billBoardService.UpdateBillBoardOnFloorChange(message.GetFloor());
                m_billBoardService.ResetBillBoardsAfterResume();
                
            }

            void BillBoardInteriorStateChangedObserver::OnInteriorExit(const InteriorsExplorer::InteriorsExplorerExitMessage &message)
            {
                m_billBoardService.RemoveAllRenderables();
                m_billBoardService.StopResetVideoService();
                m_billBoardService.ReSetFloorIndex();
                m_billBoardService.RemoveAllBillboards();
            }
            
            void BillBoardInteriorStateChangedObserver::OnDraggedFloor(const InteriorsExplorer::InteriorsExplorerFloorSelectionDraggedMessage &message)
            {
            }
            
            void BillBoardInteriorStateChangedObserver::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
                if (message.GetAppMode() == AppModes::SdkModel::InteriorMode)
                {
                    const std::string& interiorName = m_interiorsPresentationModule.GetInteriorSelectionModel().GetSelectedInteriorId().Value();
                
                    if(interiorName == "98a265e2-b890-4c6b-a28f-948c92e36914" || interiorName == "70f9b00f-8c4f-4570-9a23-62bd80a76f8a")
                    {
                        m_messageBus.Publish(ExampleApp::SearchMenu::SearchMenuPerformedSearchMessage("advertisements", true, true));
                    }
 
                }
                else
                {
                    m_messageBus.Publish(SearchResultSection::SearchResultViewClearedMessage());
                }
            }
        }
    }
}
