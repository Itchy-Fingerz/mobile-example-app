// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>

namespace ExampleApp
{
    namespace QRScan
    {
        class OnOutdoorQRScanCompleteMessage
        {
            double m_latitude;
            double m_longitude;
            double m_orientation;
            double m_zoomLevel;
            double m_tiltAngle;
            
        public:
            OnOutdoorQRScanCompleteMessage(double latitude, double longitude, double orientation, double zoomLevel, double tiltAngle);
            
            double GetLatitude() const;
            double GetLongitude() const;
            double GetOrientation() const;
            double GetZoomLevel() const;
            double GetTiltAngle() const;
        };
    }
}
