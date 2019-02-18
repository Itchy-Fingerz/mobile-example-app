// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OnOutdoorQRScanCompleteMessage.h"

namespace ExampleApp
{
    namespace QRScan
    {
        OnOutdoorQRScanCompleteMessage::OnOutdoorQRScanCompleteMessage(double latitude, double longitude, double orientation, double zoomLevel)
        : m_latitude(latitude)
        , m_longitude(longitude)
        , m_orientation(orientation)
        , m_zoomLevel(zoomLevel)
        {
        }
        
        double OnOutdoorQRScanCompleteMessage::GetLatitude() const
        {
            return m_latitude;
        }
        
        double OnOutdoorQRScanCompleteMessage::GetLongitude() const
        {
            return m_longitude;
        }
        
        double OnOutdoorQRScanCompleteMessage::GetOrientation() const
        {
            return m_orientation;
        }
        
        double OnOutdoorQRScanCompleteMessage::GetZoomLevel() const
        {
            return m_zoomLevel;
        }
    }
}
