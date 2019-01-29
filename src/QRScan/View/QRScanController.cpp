// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanController.h"
#include "LatLongAltitude.h"

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
                m_view.SetContent(m_viewModel.GetContent(false));
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
            
            void QRScanController::OnLogoLongPress()
            {
                m_view.SetContent(m_viewModel.GetContent(true));
            }

            void QRScanController::OnQRScanCompleted(const std::string& hostName, const std::string& buildingId, const std::map<std::string, double>& location)
            {
                double latitude = location.find("latitude")->second;
                double longitude = location.find("longitude")->second;
                double orientation = location.find("orientation")->second;

                m_locationProvider.EnableFixedLocation(Eegeo::Space::LatLong::FromDegrees(latitude, longitude),buildingId,0,orientation);
            }
            
            void QRScanController::OnQRScanIndoorPositionTypeMessage(const QRScan::QRScanIndoorPositionTypeMessage& message)
            {
                m_viewModel.SetIndoorPositioningType(message.GetIndoorPositioningType());
            }

            void QRScanController::OnQRScanIndoorPositionSettingsMessage(const QRScan::QRScanIndoorPositionSettingsMessage& message)
            {
                m_viewModel.SetIndoorPositionSettings(message.GetApiKey(), message.GetApiSecret(), message.GetFloorMap(), message.GetInteriorId());
            }

            void QRScanController::OnQRScanSenionDataMessage(const QRScan::QRScanSenionDataMessage& message)
            {
                m_viewModel.SetSenionData(message.GetEegeoFloorNumber(), message.GetSenionFloorNumber(), message.GetSenionLatitude(), message.GetSenionLongitude());
            }

            void QRScanController::OnQRScanIndoorAtlasDataMessage(const QRScan::QRScanIndoorAtlasDataMessage& message)
            {
                m_viewModel.SetIndoorAtlasData(message.GetEegeoFloorIndex(), message.GetIndoorAtlasFloorId(), message.GetLatitude(), message.GetLongitude());
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
                                               Metrics::IMetricsService& metricsService,
                                               ExampleAppMessaging::TMessageBus& messageBus)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_locationProvider(locationProvider)
                , m_metricsService(metricsService)
                , m_viewClosed(this, &QRScanController::OnClose)
                , m_viewOpened(this, &QRScanController::OnOpen)
                , m_viewCloseTapped(this, &QRScanController::OnCloseTapped)
                , m_logoLongPress(this, &QRScanController::OnLogoLongPress)
                , m_qrScanCompleted(this, &QRScanController::OnQRScanCompleted)
                , m_messageBus(messageBus)
                , m_qrScanIndoorPositionTypeMessageHandler(this, &QRScanController::OnQRScanIndoorPositionTypeMessage)
                , m_qrScanIndoorPositionSettingsMessageHandler(this, &QRScanController::OnQRScanIndoorPositionSettingsMessage)
                , m_qrScanSenionDataMessageHandler(this, &QRScanController::OnQRScanSenionDataMessage)
                , m_qrScanIndoorAtlasDataMessageHandler(this, &QRScanController::OnQRScanIndoorAtlasDataMessage)
                , m_appModeChangedMessageHandler(this, &QRScanController::OnAppModeChanged)
            {
                m_view.InsertCloseTappedCallback(m_viewCloseTapped);
                m_viewModel.InsertClosedCallback(m_viewClosed);
                m_viewModel.InsertOpenedCallback(m_viewOpened);
                m_view.InsertLogoLongPressCallback(m_logoLongPress);
                m_view.InsertOnQRScanCompletedCallback(m_qrScanCompleted);
                m_messageBus.SubscribeUi(m_qrScanIndoorPositionTypeMessageHandler);
                m_messageBus.SubscribeUi(m_qrScanIndoorPositionSettingsMessageHandler);
                m_messageBus.SubscribeUi(m_qrScanSenionDataMessageHandler);
                m_messageBus.SubscribeUi(m_qrScanIndoorAtlasDataMessageHandler);
                m_messageBus.SubscribeUi(m_appModeChangedMessageHandler);
            }

            QRScanController::~QRScanController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedMessageHandler);
                m_messageBus.UnsubscribeUi(m_qrScanIndoorAtlasDataMessageHandler);
                m_messageBus.UnsubscribeUi(m_qrScanSenionDataMessageHandler);
                m_messageBus.UnsubscribeUi(m_qrScanIndoorPositionSettingsMessageHandler);
                m_messageBus.UnsubscribeUi(m_qrScanIndoorPositionTypeMessageHandler);
                m_view.RemoveOnQRScanCompletedCallback(m_qrScanCompleted);
                m_view.RemoveLogoLongPressCallback(m_logoLongPress);
                m_viewModel.RemoveOpenedCallback(m_viewOpened);
                m_viewModel.RemoveClosedCallback(m_viewClosed);
                m_view.RemoveCloseTappedCallback(m_viewCloseTapped);
            }
        }
    }
}
