// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanMessageHandler.h"
#include "MarkerBuilder.h"
#include "QRCodePopUpSprite.h"

namespace ExampleApp
{
    namespace QRScanMessageHandler
    {
        QRScanMessageHandler::QRScanMessageHandler(QRCodePopUp::QRCodePopUpSprite& billBoardSprite, ExampleApp::PopUp::View::IPopUpViewModel& popUpViewModel, ExampleAppMessaging::TMessageBus& messageBus)
        : m_bilboardSprite(billBoardSprite)
        , m_popUpViewModel(popUpViewModel)
        , m_messageBus(messageBus)
        , m_indoorQrScanCompleted(this, &QRScanMessageHandler::OnIndoorQRScanCompleted)
        , m_outdoorQrScanCompleted(this, &QRScanMessageHandler::OnOutdoorQRScanCompleted)
        , m_interiorsExplorerExitMessageHandler(this,&QRScanMessageHandler::OnInteriorsExplorerExitMessage)
        , m_InteriorsExplorerFloorSelectionDraggedMessageHandler(this,&QRScanMessageHandler::OnInteriorsExplorerFloorSelectionDraggedMessage)
        {
            m_messageBus.SubscribeNative(m_indoorQrScanCompleted);
            m_messageBus.SubscribeNative(m_outdoorQrScanCompleted);
            m_messageBus.SubscribeNative(m_interiorsExplorerExitMessageHandler);
            m_messageBus.SubscribeNative(m_InteriorsExplorerFloorSelectionDraggedMessageHandler);
        }
        
        QRScanMessageHandler::~QRScanMessageHandler()
        {
            m_messageBus.UnsubscribeNative(m_indoorQrScanCompleted);
            m_messageBus.UnsubscribeNative(m_outdoorQrScanCompleted);
            m_messageBus.UnsubscribeNative(m_interiorsExplorerExitMessageHandler);
            m_messageBus.UnsubscribeNative(m_InteriorsExplorerFloorSelectionDraggedMessageHandler);
        }
        
        void QRScanMessageHandler::OnIndoorQRScanCompleted(const QRScan::OnIndoorQRScanCompleteMessage& message)
        {
//            double latitude = message.GetLatitude();
//            double longitude = message.GetLongitude();
//            const Eegeo::Space::LatLongAltitude spritePosition = Eegeo::Space::LatLongAltitude::FromDegrees(latitude, longitude, 10.0);
//            float spirteSize = message.GetZoomLevel()* 0.05;
//            m_bilboardSprite.Show(spritePosition.ToECEF(),Eegeo::v2(spirteSize, spirteSize));
        }
        
        void QRScanMessageHandler::OnOutdoorQRScanCompleted(const QRScan::OnOutdoorQRScanCompleteMessage& message)
        {
//            double latitude = message.GetLatitude();
//            double longitude = message.GetLongitude();
//            const Eegeo::Space::LatLongAltitude spritePosition = Eegeo::Space::LatLongAltitude::FromDegrees(latitude, longitude, 30.0);
//
//            float spirteSize = message.GetZoomLevel()* 0.1;
//            m_bilboardSprite.Show(spritePosition.ToECEF(),Eegeo::v2(spirteSize, spirteSize));
        }
        
        void QRScanMessageHandler::OnInteriorsExplorerExitMessage(const InteriorsExplorer::InteriorsExplorerExitMessage &message)
        {
            m_bilboardSprite.Remove();
            m_popUpViewModel.Close();
        }
        
        void QRScanMessageHandler::OnInteriorsExplorerFloorSelectionDraggedMessage(const InteriorsExplorer::InteriorsExplorerFloorSelectionDraggedMessage &message)
        {
            m_bilboardSprite.Remove();
            m_popUpViewModel.Close();
        }

    }
}
