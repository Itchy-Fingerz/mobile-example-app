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

            void QRScanController::OnQRScanCompleted(const std::string& hostName, const std::string& buildingId, const std::map<std::string, double>& location)
            {
                double latitude = location.find("latitude")->second;
                double longitude = location.find("longitude")->second;
                double orientation = location.find("orientation")->second;

                Eegeo::Space::LatLong loc = Eegeo::Space::LatLong::FromDegrees(latitude, longitude);
                m_locationProvider.EnableFixedLocation(loc,buildingId,0,orientation);
                m_cameraTransitionController.StartTransitionTo(loc.ToECEF(),
                        InteriorsExplorer::DefaultInteriorSearchResultTransitionInterestDistance,
                        buildingId,
                        0);
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
                                               Metrics::IMetricsService& metricsService,
                                               ExampleAppMessaging::TMessageBus& messageBus)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_locationProvider(locationProvider)
                , m_cameraTransitionController(cameraTransitionController)
                , m_metricsService(metricsService)
                , m_viewClosed(this, &QRScanController::OnClose)
                , m_viewOpened(this, &QRScanController::OnOpen)
                , m_viewCloseTapped(this, &QRScanController::OnCloseTapped)
                , m_qrScanCompleted(this, &QRScanController::OnQRScanCompleted)
                , m_messageBus(messageBus)
                , m_appModeChangedMessageHandler(this, &QRScanController::OnAppModeChanged)
            {
                m_view.InsertCloseTappedCallback(m_viewCloseTapped);
                m_viewModel.InsertClosedCallback(m_viewClosed);
                m_viewModel.InsertOpenedCallback(m_viewOpened);
                m_view.InsertOnQRScanCompletedCallback(m_qrScanCompleted);
                m_messageBus.SubscribeUi(m_appModeChangedMessageHandler);
            }

            QRScanController::~QRScanController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedMessageHandler);
                m_view.RemoveOnQRScanCompletedCallback(m_qrScanCompleted);
                m_viewModel.RemoveOpenedCallback(m_viewOpened);
                m_viewModel.RemoveClosedCallback(m_viewClosed);
                m_view.RemoveCloseTappedCallback(m_viewCloseTapped);
            }
        }
    }
}
