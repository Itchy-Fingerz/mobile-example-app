// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OnIndoorQRScanCompleteMessage.h"

namespace ExampleApp
{
    namespace QRScan
    {
        OnIndoorQRScanCompleteMessage::OnIndoorQRScanCompleteMessage(double latitude, double longitude, std::string buildingId, int floorIndex, double orientation, double zoomLevel)
        : m_latitude(latitude)
        , m_longitude(longitude)
        , m_buildingId(buildingId)
        , m_floorIndex(floorIndex)
        , m_orientation(orientation)
        , m_zoomLevel(zoomLevel)
        {
        }
        
        double OnIndoorQRScanCompleteMessage::GetLatitude() const
        {
            return m_latitude;
        }
        
        double OnIndoorQRScanCompleteMessage::GetLongitude() const
        {
            return m_longitude;
        }
        
        std::string OnIndoorQRScanCompleteMessage::GetBuildingId() const
        {
            return m_buildingId;
        }
        
        int OnIndoorQRScanCompleteMessage::GetFloorIndex() const
        {
            return m_floorIndex;
        }
        
        double OnIndoorQRScanCompleteMessage::GetOrientation() const
        {
            return m_orientation;
        }
        
        double OnIndoorQRScanCompleteMessage::GetZoomLevel() const
        {
            return m_zoomLevel;
        }
    }
}
