// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardInteriorStateChangedObserver.h"
#include "SearchMenuPerformedSearchMessage.h"
#include "InteriorSelectionModel.h"
#include "FixedIndoorLocationCompassModeObserver.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            BillBoardInteriorStateChangedObserver::BillBoardInteriorStateChangedObserver(ExampleAppMessaging::TMessageBus& messageBus
                                                                                         ,View::BillBoardService& billBoardService,
                                                                                         Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule, Compass::SdkModel::ICompassModel& model)
            : m_selectFloorCallback(this,&BillBoardInteriorStateChangedObserver::OnSelectFloor)
            , m_messageBus(messageBus)
            , m_billBoardService(billBoardService)
            , m_appModeChangedCallback(this, &BillBoardInteriorStateChangedObserver::OnAppModeChanged)
            , m_interiorsPresentationModule(interiorsPresentationModule)
            , m_interiorsExplorerModeChangedCallback(this,&BillBoardInteriorStateChangedObserver::OnInteriorsExplorerStateChanged)
            , m_handleSearchResultSectionItemSelectedMessageBinding(this,&BillBoardInteriorStateChangedObserver::OnSearchResultSectionItemSelectedMessage)
            , m_callback(this, &BillBoardInteriorStateChangedObserver::OnCompassClickedForMockedLocation)
            , m_model(model)
            {
                m_messageBus.SubscribeNative(m_selectFloorCallback);
                m_messageBus.SubscribeUi(m_appModeChangedCallback);
                m_messageBus.SubscribeUi(m_interiorsExplorerModeChangedCallback);
                m_messageBus.SubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);

                model.InsertGpsModeChangedCallback(m_callback);
            }
            
            BillBoardInteriorStateChangedObserver::~BillBoardInteriorStateChangedObserver()
            {
                m_messageBus.UnsubscribeNative(m_selectFloorCallback);
                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);
                m_messageBus.UnsubscribeUi(m_interiorsExplorerModeChangedCallback);
                m_messageBus.UnsubscribeNative(m_handleSearchResultSectionItemSelectedMessageBinding);
                m_model.RemoveGpsModeChangedCallback(m_callback);

            }
            
            void BillBoardInteriorStateChangedObserver::OnSelectFloor(const InteriorsExplorer::InteriorsExplorerSelectFloorMessage &message)
            {
                m_billBoardService.OnFloorChange(message.GetFloor());
                
            }
            
            void BillBoardInteriorStateChangedObserver::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
                if (message.GetAppMode() == AppModes::SdkModel::WorldMode)
                {
                    m_billBoardService.OnInteriorsExit();
                }
            }
            
            void BillBoardInteriorStateChangedObserver::OnInteriorsExplorerStateChanged(const InteriorsExplorer::InteriorsExplorerStateChangedMessage& message)
            {
                const std::string& interiorName = m_interiorsPresentationModule.GetInteriorSelectionModel().GetSelectedInteriorId().Value();
                
                if((interiorName == "98a265e2-b890-4c6b-a28f-948c92e36914" || interiorName == "70f9b00f-8c4f-4570-9a23-62bd80a76f8a") && message.IsInteriorVisible())    // Currently enabled for Lax and WestPort House
                {
                    m_messageBus.Publish(ExampleApp::SearchMenu::SearchMenuPerformedSearchMessage("advertisements", true, true));
                }
            }
            
            void BillBoardInteriorStateChangedObserver::OnSearchResultSectionItemSelectedMessage(const SearchResultSection::SearchResultSectionItemSelectedMessage& message)
            {
                if(message.FloorIndex() != m_billBoardService.GetFloorIndex())
                {
                    m_billBoardService.OnFloorChange(message.FloorIndex());
                }
                
            }
            
            void BillBoardInteriorStateChangedObserver::OnCompassClickedForMockedLocation()
            {
                if(m_billBoardService.GetFloorIndex() != FIXED_MY_LOCATION_FLOOR_INDEX) // NOTE: Floor number for mocked location
                {
                    m_billBoardService.OnFloorChange(FIXED_MY_LOCATION_FLOOR_INDEX);
                }
            }
            
        }
    }
}
