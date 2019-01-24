// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "QRScanViewIncludes.h"
#include "QRScan.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            class IQRScanViewModule
            {
            public:
                virtual ~IQRScanViewModule() { }

                virtual QRScanView& GetQRScanView() const = 0;
                virtual QRScanController& GetQRScanController() const = 0;
            };
        }
    }
}
