// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include <string>
#include <map>

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            class IQRScanView
            {
            public:
                virtual ~IQRScanView() { };
                virtual void Open() = 0;
                virtual void Close() = 0;
                virtual void OnIndoorQRScanCompleted(double lat, double lng, const std::string& buildingId, int floorIndex, double orientation, double zoomLevel, double tiltAngle) = 0;
                virtual void OnOutdoorQRScanCompleted(double lat, double lng, double orientation, double zoomLevel, double tiltAngle) = 0;

                virtual void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
