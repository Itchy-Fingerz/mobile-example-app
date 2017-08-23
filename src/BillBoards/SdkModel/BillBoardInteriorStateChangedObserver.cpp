// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardInteriorStateChangedObserver.h"
#include "SearchMenuPerformedSearchMessage.h"
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
            , m_messageBus(messageBus)
            , m_billBoardService(billBoardService)
            , m_appModeChangedCallback(this, &BillBoardInteriorStateChangedObserver::OnAppModeChanged)
            , m_interiorsPresentationModule(interiorsPresentationModule)
            , m_interiorsExplorerModeChangedCallback(this,&BillBoardInteriorStateChangedObserver::OnInteriorsExplorerStateChanged)
            {
                m_messageBus.SubscribeNative(m_selectFloorCallback);
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
                m_messageBus.SubscribeUi(m_interiorsExplorerModeChangedCallback);
            }
            
            BillBoardInteriorStateChangedObserver::~BillBoardInteriorStateChangedObserver()
            {
                m_messageBus.UnsubscribeNative(m_selectFloorCallback);
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
            }
            
            void BillBoardInteriorStateChangedObserver::OnSelectFloor(const InteriorsExplorer::InteriorsExplorerSelectFloorMessage &message)
            {
                m_billBoardService.PartialRefreshService();
                
                m_billBoardService.SetFloorIndex(message.GetFloor());
                m_billBoardService.CreateBillBoardsFromConfigList();
            }
            
            void BillBoardInteriorStateChangedObserver::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
                if (message.GetAppMode() == AppModes::SdkModel::WorldMode)
                {
                    m_billBoardService.FullRefreshService();
                }
            }
            
            void BillBoardInteriorStateChangedObserver::OnInteriorsExplorerStateChanged(const InteriorsExplorer::InteriorsExplorerStateChangedMessage& message)
            {
                const std::string& interiorName = m_interiorsPresentationModule.GetInteriorSelectionModel().GetSelectedInteriorId().Value();
                
                if(interiorName == "98a265e2-b890-4c6b-a28f-948c92e36914" || interiorName == "70f9b00f-8c4f-4570-9a23-62bd80a76f8a")    // Currently enabled for Lax and WestPort House
                {
                    m_messageBus.Publish(ExampleApp::SearchMenu::SearchMenuPerformedSearchMessage("advertisements", true, true));
                }
            }
            
        }
    }
}
