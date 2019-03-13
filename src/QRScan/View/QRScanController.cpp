// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanController.h"
#include "LatLongAltitude.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            void QRScanController::OnOpen()
            {
                m_metricsService.SetEvent("UIItem: QR Scan");
                m_metricsService.BeginTimedEvent("TimedEvent: Viewing QR Scan");
                m_view.Open();
            }

            void QRScanController::OnClose()
            {
                m_metricsService.EndTimedEvent("TimedEvent: Viewing About Page");
                m_view.Close();
            }

            void QRScanController::OnCloseTapped()
            {
                if (m_viewModel.IsOpen())
                {
                    m_viewModel.Close();
                }
            }

            void QRScanController::OnIndoorQRScanCompleted(const QRScan::OnIndoorQRScanCompleteMessage& message)
            {
                double latitude = message.GetLatitude();
                double longitude = message.GetLongitude();
                std::string buildingId = message.GetBuildingId();
                int floorIndex = message.GetFloorIndex();
                double orientation = message.GetOrientation();
                double zoomLevel = message.GetZoomLevel();
                double tiltAngle = message.GetTiltAngle();

                Eegeo::Space::LatLong loc = Eegeo::Space::LatLong::FromDegrees(latitude, longitude);
                m_locationProvider.EnableFixedLocation(loc,buildingId,floorIndex,orientation);
                const float heading = Eegeo::Math::Deg2Rad(orientation);
                const Eegeo::dv3 interestPoint = loc.ToECEF();
                Eegeo_TTY("najhi x:%d y:%d z:%d", interestPoint.x, interestPoint.y,interestPoint.z);
                m_cameraTransitionController.StartTransitionTo(interestPoint,
                                                               zoomLevel,
                                                               heading,
                                                               buildingId,
                                                               floorIndex,
                                                               true,
                                                               true,
                                                               true,
                                                               true);
                m_interiorsCameraController.SetTilt(tiltAngle);
            }

            void QRScanController::OnOutdoorQRScanCompleted(const QRScan::OnOutdoorQRScanCompleteMessage& message)
            {
                double latitude = message.GetLatitude();
                double longitude = message.GetLongitude();
                double orientation = message.GetOrientation();
                double zoomLevel = message.GetZoomLevel();
                double tiltAngle = message.GetTiltAngle();

                Eegeo::Space::LatLong loc = Eegeo::Space::LatLong::FromDegrees(latitude, longitude);
                m_locationProvider.EnableFixedLocation(loc,Eegeo::Resources::Interiors::InteriorId(""),0,orientation);
                const float heading = Eegeo::Math::Deg2Rad(orientation);
                m_cameraTransitionController.StartTransitionTo(loc.ToECEF(),
                                                               zoomLevel,
                                                               heading);
                m_globeCameraController.ApplyTilt(tiltAngle);
            }
            
            void QRScanController::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                if (message.GetAppMode() == AppModes::SdkModel::AppMode::AttractMode && m_viewModel.IsOpen())
                {
                    m_viewModel.Close();
                }
            }

            QRScanController::QRScanController(IQRScanView& view, IQRScanViewModel& viewModel,
                                               LocationProvider::ILocationProvider& locationProvider,
                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                               Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                               Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController,
                                               Metrics::IMetricsService& metricsService,
                                               ExampleAppMessaging::TMessageBus& messageBus)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_locationProvider(locationProvider)
                , m_cameraTransitionController(cameraTransitionController)
                , m_interiorsCameraController(interiorsCameraController)
                , m_globeCameraController(globeCameraController)
                , m_metricsService(metricsService)
                , m_viewClosed(this, &QRScanController::OnClose)
                , m_viewOpened(this, &QRScanController::OnOpen)
                , m_viewCloseTapped(this, &QRScanController::OnCloseTapped)
                , m_indoorQrScanCompleted(this, &QRScanController::OnIndoorQRScanCompleted)
                , m_outdoorQrScanCompleted(this, &QRScanController::OnOutdoorQRScanCompleted)
                , m_messageBus(messageBus)
                , m_appModeChangedMessageHandler(this, &QRScanController::OnAppModeChanged)
            {
                m_view.InsertCloseTappedCallback(m_viewCloseTapped);
                m_viewModel.InsertClosedCallback(m_viewClosed);
                m_viewModel.InsertOpenedCallback(m_viewOpened);
                m_messageBus.SubscribeNative(m_indoorQrScanCompleted);
                m_messageBus.SubscribeNative(m_outdoorQrScanCompleted);
                m_messageBus.SubscribeUi(m_appModeChangedMessageHandler);
            }

            QRScanController::~QRScanController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedMessageHandler);
                m_messageBus.UnsubscribeNative(m_indoorQrScanCompleted);
                m_messageBus.UnsubscribeNative(m_outdoorQrScanCompleted);
                m_viewModel.RemoveOpenedCallback(m_viewOpened);
                m_viewModel.RemoveClosedCallback(m_viewClosed);
                m_view.RemoveCloseTappedCallback(m_viewCloseTapped);
            }
        }
    }
}
