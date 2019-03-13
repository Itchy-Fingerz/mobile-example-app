// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanViewModule.h"
#include "QRScan.h"
#include "QRScanView.h"
#include "QRScanController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            QRScanViewModule::QRScanViewModule(
                AndroidNativeState& nativeState,
                IQRScanViewModel& qrScanViewModel,
                LocationProvider::ILocationProvider& locationProvider,
                CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                Metrics::IMetricsService& metricsService,
				ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD
                m_pView = Eegeo_NEW(QRScanView)(nativeState, messageBus);
                m_pController = Eegeo_NEW(QRScanController)(*m_pView, qrScanViewModel, locationProvider, cameraTransitionController, interiorsCameraController, globeCameraController, metricsService, messageBus);
            }

            QRScanViewModule::~QRScanViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE(m_pController);
                Eegeo_DELETE(m_pView);
            }

            QRScanController& QRScanViewModule::GetQRScanController() const
            {
                ASSERT_UI_THREAD
                return *m_pController;
            }

            QRScanView& QRScanViewModule::GetQRScanView() const
            {
                ASSERT_UI_THREAD
                return *m_pView;
            }
        }
    }
}
