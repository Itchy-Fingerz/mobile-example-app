// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "BidirectionalBus.h"
#include "BillBoardService.h"
#include "InteriorsExplorerSelectFloorMessage.h"
#include "InteriorsExplorerFloorSelectionDraggedMessage.h"

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
                                                      Eegeo::Modules::Map::Layers::InteriorsPresentationModule& interiorsPresentationModule);
                ~BillBoardInteriorStateChangedObserver();

            private:                
                Eegeo::Helpers::TCallback1<BillBoardInteriorStateChangedObserver, const InteriorsExplorer::InteriorsExplorerSelectFloorMessage&> m_selectFloorCallback;
                Eegeo::Helpers::TCallback1<BillBoardInteriorStateChangedObserver, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                
                View::BillBoardService& m_billBoardService;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Modules::Map::Layers::InteriorsPresentationModule& m_interiorsPresentationModule;
                
                void OnSelectFloor(const InteriorsExplorer::InteriorsExplorerSelectFloorMessage &message);
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
            };
        }
    }
}
