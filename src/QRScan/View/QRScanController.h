// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "QRScan.h"
#include "ICallback.h"
#include "IQRScanViewModel.h"
#include "IQRScanView.h"
#include "IMetricsService.h"
#include "QRScanIndoorPositionTypeMessage.h"
#include "QRScanSenionDataMessage.h"
#include "QRScanIndoorPositionSettingsMessage.h"
#include "BidirectionalBus.h"
#include "ILocationProvider.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            class QRScanController : private Eegeo::NonCopyable
            {
            private:
                IQRScanView& m_view;
                IQRScanViewModel& m_viewModel;
                LocationProvider::ILocationProvider& m_locationProvider;

                Eegeo::Helpers::TCallback0<QRScanController> m_viewOpened;
                Eegeo::Helpers::TCallback0<QRScanController> m_viewClosed;
                Eegeo::Helpers::TCallback0<QRScanController> m_viewCloseTapped;
                Eegeo::Helpers::TCallback0<QRScanController> m_logoLongPress;
                Eegeo::Helpers::TCallback3<QRScanController, const std::string&, const std::string&, const std::map<std::string, double>&> m_qrScanCompleted;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Metrics::IMetricsService& m_metricsService;
                
                Eegeo::Helpers::TCallback1<QRScanController, const QRScanIndoorPositionTypeMessage&> m_qrScanIndoorPositionTypeMessageHandler;
                Eegeo::Helpers::TCallback1<QRScanController, const QRScanIndoorPositionSettingsMessage&> m_qrScanIndoorPositionSettingsMessageHandler;
                Eegeo::Helpers::TCallback1<QRScanController, const QRScanSenionDataMessage&> m_qrScanSenionDataMessageHandler;
                Eegeo::Helpers::TCallback1<QRScanController, const QRScanIndoorAtlasDataMessage&> m_qrScanIndoorAtlasDataMessageHandler;
                Eegeo::Helpers::TCallback1<QRScanController, const AppModes::AppModeChangedMessage&> m_appModeChangedMessageHandler;

                void OnOpen();
                void OnClose();
                void OnCloseTapped();
                void OnLogoLongPress();
                void OnQRScanCompleted(const std::string& hostName, const std::string& buildingId, const std::map<std::string, double>& location);
                
                void OnQRScanIndoorPositionTypeMessage(const QRScan::QRScanIndoorPositionTypeMessage& message);
                void OnQRScanIndoorPositionSettingsMessage(const QRScan::QRScanIndoorPositionSettingsMessage& message);
                void OnQRScanSenionDataMessage(const QRScan::QRScanSenionDataMessage& message);
                void OnQRScanIndoorAtlasDataMessage(const QRScan::QRScanIndoorAtlasDataMessage& message);
                void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);

            public:
                QRScanController(IQRScanView& view, IQRScanViewModel& viewModel, LocationProvider::ILocationProvider& locationProvider, Metrics::IMetricsService& metricsService, ExampleAppMessaging::TMessageBus& messageBus);

                ~QRScanController();
            };
        }
    }
}
