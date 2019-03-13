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
            class IQRScanViewModel
            {
            public:
                virtual ~IQRScanViewModel() { }

                virtual bool IsOpen() const = 0;

                virtual void Open() = 0;

                virtual void Close() = 0;
                
                virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
                
            };
        }
    }
}
