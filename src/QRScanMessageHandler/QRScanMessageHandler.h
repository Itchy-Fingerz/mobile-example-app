// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "QRCodePopUpSprite.h"
#include "InteriorsExplorerExitMessage.h"
#include "InteriorsExplorerFloorSelectionDraggedMessage.h"

namespace ExampleApp
{
    namespace QRScanMessageHandler
    {
        class QRScanMessageHandler
        {
        private:
            
            ExampleAppMessaging::TMessageBus& m_messageBus;
            Eegeo::Helpers::TCallback1<QRScanMessageHandler, const QRScan::OnIndoorQRScanCompleteMessage&> m_indoorQrScanCompleted;
            Eegeo::Helpers::TCallback1<QRScanMessageHandler, const QRScan::OnOutdoorQRScanCompleteMessage&> m_outdoorQrScanCompleted;
            Eegeo::Helpers::TCallback1<QRScanMessageHandler, const InteriorsExplorer::InteriorsExplorerExitMessage&> m_interiorsExplorerExitMessageHandler;
            Eegeo::Helpers::TCallback1<QRScanMessageHandler, const InteriorsExplorer::InteriorsExplorerFloorSelectionDraggedMessage&> m_InteriorsExplorerFloorSelectionDraggedMessageHandler;


            
            QRCodePopUp::QRCodePopUpSprite& m_bilboardSprite;

            void OnIndoorQRScanCompleted(const QRScan::OnIndoorQRScanCompleteMessage& message);
            void OnOutdoorQRScanCompleted(const QRScan::OnOutdoorQRScanCompleteMessage& message);
            
            void OnInteriorsExplorerExitMessage(const InteriorsExplorer::InteriorsExplorerExitMessage &message);
            void OnInteriorsExplorerFloorSelectionDraggedMessage(const InteriorsExplorer::InteriorsExplorerFloorSelectionDraggedMessage &message);
                        
        public:
            QRScanMessageHandler(QRCodePopUp::QRCodePopUpSprite& billBoardSprite,ExampleAppMessaging::TMessageBus& messageBus);
            ~QRScanMessageHandler();
            
        };
    }
}
