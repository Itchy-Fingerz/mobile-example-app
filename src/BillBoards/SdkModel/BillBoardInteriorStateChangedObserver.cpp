// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardInteriorStateChangedObserver.h"
#include "SearchMenuPerformedSearchMessage.h"
#include "SetCustomAlertVisibilityMessage.h"
namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            BillBoardInteriorStateChangedObserver::BillBoardInteriorStateChangedObserver(ExampleAppMessaging::TMessageBus& messageBus
                 ,View::BillBoardService& billBoardService)
            : m_selectFloorCallback(this,&BillBoardInteriorStateChangedObserver::OnSelectFloor)
            , m_exitInteriorCallback(this,&BillBoardInteriorStateChangedObserver::OnInteriorExit)
            , m_draggedFloorCallback(this,&BillBoardInteriorStateChangedObserver::OnDraggedFloor)
            , m_messageBus(messageBus)
            , m_billBoardService(billBoardService)
            , m_appModeChangedCallback(this, &BillBoardInteriorStateChangedObserver::OnAppModeChanged)

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
                    m_messageBus.Publish(ExampleApp::SearchMenu::SearchMenuPerformedSearchMessage("advertisements", true, true));
 
                }
                else
                {
                    m_messageBus.Publish(SearchResultSection::SearchResultViewClearedMessage());
                }
            }
        }
    }
}
