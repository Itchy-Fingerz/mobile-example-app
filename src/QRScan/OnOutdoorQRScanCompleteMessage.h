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
            
        public:
            OnOutdoorQRScanCompleteMessage(double latitude, double longitude, double orientation, double zoomLevel);
            
            double GetLatitude() const;
            double GetLongitude() const;
            double GetOrientation() const;
            double GetZoomLevel() const;
        };
    }
}
