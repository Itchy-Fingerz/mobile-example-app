// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>

namespace ExampleApp
{
    namespace QRScan
    {
        class OnIndoorQRScanCompleteMessage
        {
            double m_latitude;
            double m_longitude;
            std::string m_buildingId;
            int m_floorIndex;
            double m_orientation;
            double m_zoomLevel;
            
        public:
            OnIndoorQRScanCompleteMessage(double latitude, double longitude, std::string buildingId, int floorIndex, double orientation, double zoomLevel);
            
            double GetLatitude() const;
            double GetLongitude() const;
            std::string GetBuildingId() const;
            int GetFloorIndex() const;
            double GetOrientation() const;
            double GetZoomLevel() const;
        };
    }
}
