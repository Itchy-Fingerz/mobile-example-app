// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "QRScan.h"
#include "QRScanViewIncludes.h"
#include "IQRScanViewModule.h"
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
            class QRScanViewModule: public IQRScanViewModule, private Eegeo::NonCopyable
            {
            private:
                QRScanView* m_pView;
                QRScanController* m_pController;

            public:
                QRScanViewModule(
                    AndroidNativeState& nativeState,
                    IQRScanViewModel& qrScanViewModel,
                    LocationProvider::ILocationProvider& locationProvider,
                    CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                    Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                    Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                    ExampleApp::PopUp::View::IPopUpViewModel& popUpViewModel,
                    Metrics::IMetricsService& metricsService,
					ExampleAppMessaging::TMessageBus& messageBus
                );

                ~QRScanViewModule();

                QRScanController& GetQRScanController() const;
                QRScanView& GetQRScanView() const;
            };
        }
    }
}