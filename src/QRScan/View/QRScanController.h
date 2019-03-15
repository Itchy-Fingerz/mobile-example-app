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
#include "InteriorsCameraController.h"
#include "GlobeCameraController.h"
#include "IPopUpViewModel.h"

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
                Eegeo::Resources::Interiors::InteriorsCameraController& m_interiorsCameraController;
                Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;
                
                Eegeo::Helpers::TCallback0<QRScanController> m_viewOpened;
                Eegeo::Helpers::TCallback0<QRScanController> m_viewClosed;
                Eegeo::Helpers::TCallback0<QRScanController> m_viewCloseTapped;
                Eegeo::Helpers::TCallback1<QRScanController, const QRScan::OnIndoorQRScanCompleteMessage&> m_indoorQrScanCompleted;
                Eegeo::Helpers::TCallback1<QRScanController, const QRScan::OnOutdoorQRScanCompleteMessage&> m_outdoorQrScanCompleted;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Metrics::IMetricsService& m_metricsService;
                
                Eegeo::Helpers::TCallback1<QRScanController, const AppModes::AppModeChangedMessage&> m_appModeChangedMessageHandler;
                Eegeo::Helpers::TCallback0<QRScanController> m_cameraTransitionCompleteCallback;
                
                ExampleApp::PopUp::View::IPopUpViewModel& m_popUpViewModel;
                Eegeo::Space::LatLong m_currentLocationSelectedFromQR;
                bool m_isInterior;
                bool m_isFromQrScan;
                
                void OnOpen();
                void OnClose();
                void OnCloseTapped();
                void OnIndoorQRScanCompleted(const QRScan::OnIndoorQRScanCompleteMessage& message);
                void OnOutdoorQRScanCompleted(const QRScan::OnOutdoorQRScanCompleteMessage& message);
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage &message);
                void HandleCameraTransitionComplete();

            public:
                QRScanController(IQRScanView& view, IQRScanViewModel& viewModel,
                                 LocationProvider::ILocationProvider& locationProvider,
                                 CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                 Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                 Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                                 Metrics::IMetricsService& metricsService,
                                 ExampleApp::PopUp::View::IPopUpViewModel& popUpViewModel,
                                 ExampleAppMessaging::TMessageBus& messageBus);

                ~QRScanController();
            };
        }
    }
}
