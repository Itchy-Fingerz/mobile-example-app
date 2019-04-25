// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanViewModule.h"
#include "IQRScanViewModel.h"
#include "QRScanView.h"
#include "QRScanController.h"
#include "QRScanViewInterop.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            QRScanViewModule::QRScanViewModule(IQRScanViewModel& qrScanViewModel,         LocationProvider::ILocationProvider& locationProvider,
               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                               Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                               Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                                               ExampleApp::PopUp::View::IPopUpViewModel& popUpViewModel,
                                               Metrics::IMetricsService& metricsService, ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pView = [QRScanView loadQRScanViewWithBus:messageBus];
                m_pController = Eegeo_NEW(QRScanController)(*[m_pView getInterop], qrScanViewModel,
                                                            locationProvider,
                                                            cameraTransitionController,
                                                            interiorsCameraController,
                                                            globeCameraController,
                                                            metricsService,
                                                            popUpViewModel,
                                                            messageBus);
            }

            QRScanViewModule::~QRScanViewModule()
            {
                Eegeo_DELETE m_pController;
                [m_pView release];
            }

            QRScanController& QRScanViewModule::GetQRScanController() const
            {
                return *m_pController;
            }

            QRScanView& QRScanViewModule::GetQRScanView() const
            {
                return *m_pView;
            }
        }
    }
}