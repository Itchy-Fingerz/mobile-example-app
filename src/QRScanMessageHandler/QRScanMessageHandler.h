// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "BillboardedSpriteExample.h"
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
            Eegeo::Helpers::TCallback1<QRScanMessageHandler, const AppModes::AppModeChangedMessage&> m_appModeChangedMessageHandler;
            
            BillboardedSprite::BillboardedSpriteExample& m_bilboardSprite;

            void OnIndoorQRScanCompleted(const QRScan::OnIndoorQRScanCompleteMessage& message);
            void OnOutdoorQRScanCompleted(const QRScan::OnOutdoorQRScanCompleteMessage& message);
            
            void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);
                        
        public:
            QRScanMessageHandler(BillboardedSprite::BillboardedSpriteExample& billBoardSprite,ExampleAppMessaging::TMessageBus& messageBus);
            ~QRScanMessageHandler();
            
        };
    }
}
