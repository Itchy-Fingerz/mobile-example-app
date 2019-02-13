// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "QRScan.h"
#include "ICallback.h"
#include "IQRScanViewModel.h"
#include "IQRScanView.h"
#include "IMetricsService.h"
#include "BidirectionalBus.h"
#include "ILocationProvider.h"
#include "ICameraTransitionController.h"

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
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;

                Eegeo::Helpers::TCallback0<QRScanController> m_viewOpened;
                Eegeo::Helpers::TCallback0<QRScanController> m_viewClosed;
                Eegeo::Helpers::TCallback0<QRScanController> m_viewCloseTapped;
                Eegeo::Helpers::TCallback3<QRScanController, const std::string&, const int&, const std::map<std::string, double>&> m_indoorQrScanCompleted;
                Eegeo::Helpers::TCallback1<QRScanController, const std::map<std::string, double>&> m_outdoorQrScanCompleted;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Metrics::IMetricsService& m_metricsService;
                
                Eegeo::Helpers::TCallback1<QRScanController, const AppModes::AppModeChangedMessage&> m_appModeChangedMessageHandler;

                void OnOpen();
                void OnClose();
                void OnCloseTapped();
                void OnIndoorQRScanCompleted(const std::string& buildingId, const int& floorIndex, const std::map<std::string, double>& locationData);
                void OnOutdoorQRScanCompleted(const std::map<std::string, double>& locationData);
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);

            public:
                QRScanController(IQRScanView& view, IQRScanViewModel& viewModel, LocationProvider::ILocationProvider& locationProvider, CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController, Metrics::IMetricsService& metricsService, ExampleAppMessaging::TMessageBus& messageBus);

                ~QRScanController();
            };
        }
    }
}
