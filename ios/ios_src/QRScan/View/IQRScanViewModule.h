// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "QRScanViewIncludes.h"

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

                virtual QRScanController& GetQRScanController() const = 0;

                virtual QRScanView& GetQRScanView() const = 0;
            };
        }
    }
}
