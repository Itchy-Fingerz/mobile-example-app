// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanMessageHandler.h"
#include "MarkerBuilder.h"

namespace ExampleApp
{
    namespace QRScanMessageHandler
    {
        QRScanMessageHandler::QRScanMessageHandler(Eegeo::Markers::IMarkerService& markerService,ExampleAppMessaging::TMessageBus& messageBus)
        : m_markerService(markerService)
        , m_messageBus(messageBus)
        , m_indoorQrScanCompleted(this, &QRScanMessageHandler::OnIndoorQRScanCompleted)
        , m_outdoorQrScanCompleted(this, &QRScanMessageHandler::OnOutdoorQRScanCompleted)
        , m_appModeChangedMessageHandler(this, &QRScanMessageHandler::OnAppModeChanged)
        {
            m_messageBus.SubscribeNative(m_indoorQrScanCompleted);
            m_messageBus.SubscribeNative(m_outdoorQrScanCompleted);
            m_messageBus.SubscribeUi(m_appModeChangedMessageHandler);

        }
        
        QRScanMessageHandler::~QRScanMessageHandler()
        {
            QRScanMessageHandler::ClearPins();
            m_messageBus.UnsubscribeNative(m_indoorQrScanCompleted);
            m_messageBus.UnsubscribeNative(m_outdoorQrScanCompleted);
            m_messageBus.UnsubscribeUi(m_appModeChangedMessageHandler);
        }
        
        void QRScanMessageHandler::OnIndoorQRScanCompleted(const QRScan::OnIndoorQRScanCompleteMessage& message)
        {
            double latitude = message.GetLatitude();
            double longitude = message.GetLongitude();
            std::string buildingId = message.GetBuildingId();
            int floorIndex = message.GetFloorIndex();
            
            QRScanMessageHandler::ClearPins();
            const auto& markerCreateParams = Eegeo::Markers::MarkerBuilder()
            .SetLocation(latitude, longitude)
            .SetLabelIcon("you_are_here")
            .SetElevation(5)
            .SetInterior(buildingId,floorIndex+1)
            .SetSubPriority(0)
            .Build();
            
            const Eegeo::Markers::IMarker::IdType markerId = m_markerService.Create(markerCreateParams);
            m_markerIDs.push_back(markerId);

        }
        
        void QRScanMessageHandler::OnOutdoorQRScanCompleted(const QRScan::OnOutdoorQRScanCompleteMessage& message)
        {
            double latitude = message.GetLatitude();
            double longitude = message.GetLongitude();

            QRScanMessageHandler::ClearPins();
            const auto& markerCreateParams = Eegeo::Markers::MarkerBuilder()
            .SetLocation(latitude, longitude)
            .SetLabelIcon("you_are_here")
            .SetElevation(5)
            .SetSubPriority(0)
            .Build();
            
            const Eegeo::Markers::IMarker::IdType markerId = m_markerService.Create(markerCreateParams);
            m_markerIDs.push_back(markerId);
        }
        
        void QRScanMessageHandler::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
        {

            
            if (message.GetAppMode() == AppModes::SdkModel::AppMode::WorldMode)
            {
                QRScanMessageHandler::ClearPins();
            }
        }
        
        void QRScanMessageHandler::ClearPins()
        {
            while(!m_markerIDs.empty())
            {
                m_markerService.Destroy(m_markerIDs.back());
                m_markerIDs.pop_back();
            }
        }

    }
}
