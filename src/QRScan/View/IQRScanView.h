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
                virtual void OnQRScanCompleted(const std::string& host, double lat, double lng, const std::string& buildingId, double orientation) = 0;

                virtual void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void InsertOnQRScanCompletedCallback(Eegeo::Helpers::ICallback3<const std::string&, const std::string&, const std::map<std::string, double>&>& callback) = 0;
                virtual void RemoveOnQRScanCompletedCallback(Eegeo::Helpers::ICallback3<const std::string&, const std::string&, const std::map<std::string, double>&>& callback) = 0;
            };
        }
    }
}
