// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "BidirectionalBus.h"
#include "BillBoardService.h"
#include "InteriorsExplorerSelectFloorMessage.h"
#include "InteriorsExplorerFloorSelectionDraggedMessage.h"
#include "InteriorsExplorerStateChangedMessage.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "ICompassModel.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            class BillBoardInteriorStateChangedObserver
            {
            public:
                BillBoardInteriorStateChangedObserver(ExampleAppMessaging::TMessageBus& messageBus
                                                      ,View::BillBoardService& billBoardService,
                                                      Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule, Compass::SdkModel::ICompassModel& model);
                ~BillBoardInteriorStateChangedObserver();

            private:                
                Eegeo::Helpers::TCallback1<BillBoardInteriorStateChangedObserver, const InteriorsExplorer::InteriorsExplorerSelectFloorMessage&> m_selectFloorCallback;
                Eegeo::Helpers::TCallback1<BillBoardInteriorStateChangedObserver, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                Eegeo::Helpers::TCallback1<BillBoardInteriorStateChangedObserver, const InteriorsExplorer::InteriorsExplorerStateChangedMessage&> m_interiorsExplorerModeChangedCallback;
                Eegeo::Helpers::TCallback1<BillBoardInteriorStateChangedObserver, const SearchResultSection::SearchResultSectionItemSelectedMessage&> m_handleSearchResultSectionItemSelectedMessageBinding;
                Eegeo::Helpers::TCallback0<BillBoardInteriorStateChangedObserver> m_callback;
                
                View::BillBoardService& m_billBoardService;
                Compass::SdkModel::ICompassModel& m_model;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Modules::Map::Layers::InteriorsPresentationModule& m_interiorsPresentationModule;
                
                void OnSelectFloor(const InteriorsExplorer::InteriorsExplorerSelectFloorMessage &message);
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                void OnInteriorsExplorerStateChanged(const InteriorsExplorer::InteriorsExplorerStateChangedMessage& message);
                
                void OnSearchResultSectionItemSelectedMessage(const SearchResultSection::SearchResultSectionItemSelectedMessage& message);
                void OnCompassClickedForMockedLocation();
            };
        }
    }
}
