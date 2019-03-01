// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanMessageHandler.h"
#include "MarkerBuilder.h"
#include "BillboardedSpriteExample.h"

namespace ExampleApp
{
    namespace QRScanMessageHandler
    {
        QRScanMessageHandler::QRScanMessageHandler(BillboardedSprite::BillboardedSpriteExample& billBoardSprite,ExampleAppMessaging::TMessageBus& messageBus)
        : m_bilboardSprite(billBoardSprite)
        , m_messageBus(messageBus)
        , m_indoorQrScanCompleted(this, &QRScanMessageHandler::OnIndoorQRScanCompleted)
        , m_outdoorQrScanCompleted(this, &QRScanMessageHandler::OnOutdoorQRScanCompleted)
        , m_appModeChangedMessageHandler(this, &QRScanMessageHandler::OnAppModeChanged)
        {
            m_messageBus.SubscribeNative(m_indoorQrScanCompleted);
            m_messageBus.SubscribeNative(m_outdoorQrScanCompleted);
            m_messageBus.SubscribeUi(m_appModeChangedMessageHandler);

        }
        
        QRScanMessageHandler::~QRScanMessageHandler()
        {
            m_messageBus.UnsubscribeNative(m_indoorQrScanCompleted);
            m_messageBus.UnsubscribeNative(m_outdoorQrScanCompleted);
            m_messageBus.UnsubscribeUi(m_appModeChangedMessageHandler);
        }
        
        void QRScanMessageHandler::OnIndoorQRScanCompleted(const QRScan::OnIndoorQRScanCompleteMessage& message)
        {
            double latitude = message.GetLatitude();
            double longitude = message.GetLongitude();
            const Eegeo::Space::LatLongAltitude spritePosition = Eegeo::Space::LatLongAltitude::FromDegrees(latitude, longitude, 30.0);
            
            m_bilboardSprite.Start(spritePosition.ToECEF());
        }
        
        void QRScanMessageHandler::OnOutdoorQRScanCompleted(const QRScan::OnOutdoorQRScanCompleteMessage& message)
        {
            double latitude = message.GetLatitude();
            double longitude = message.GetLongitude();
            const Eegeo::Space::LatLongAltitude spritePosition = Eegeo::Space::LatLongAltitude::FromDegrees(latitude, longitude, 30.0);
            
            m_bilboardSprite.Start(spritePosition.ToECEF());
        }
        
        void QRScanMessageHandler::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
        {
            if (message.GetAppMode() == AppModes::SdkModel::AppMode::WorldMode)
            {
            }
        }
    }
}
