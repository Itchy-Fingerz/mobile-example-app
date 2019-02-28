// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "Markers.h"
#include "IMarker.h"
#include "IMarkerService.h"

namespace ExampleApp
{
    namespace QRScanMessageHandler
    {
        class QRScanMessageHandler
        {
        private:
            
            Eegeo::Markers::IMarkerService& m_markerService;
            std::vector<Eegeo::Markers::IMarker::IdType> m_markerIDs;

            ExampleAppMessaging::TMessageBus& m_messageBus;
            Eegeo::Helpers::TCallback1<QRScanMessageHandler, const QRScan::OnIndoorQRScanCompleteMessage&> m_indoorQrScanCompleted;
            Eegeo::Helpers::TCallback1<QRScanMessageHandler, const QRScan::OnOutdoorQRScanCompleteMessage&> m_outdoorQrScanCompleted;
            Eegeo::Helpers::TCallback1<QRScanMessageHandler, const AppModes::AppModeChangedMessage&> m_appModeChangedMessageHandler;

            
            void OnIndoorQRScanCompleted(const QRScan::OnIndoorQRScanCompleteMessage& message);
            void OnOutdoorQRScanCompleted(const QRScan::OnOutdoorQRScanCompleteMessage& message);
            
            void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);
            
            void ClearPins();
            
        public:
            QRScanMessageHandler(Eegeo::Markers::IMarkerService& markerService,ExampleAppMessaging::TMessageBus& messageBus);
            ~QRScanMessageHandler();
            
        };
    }
}
