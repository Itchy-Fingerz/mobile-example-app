// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IOpenableControlViewModel.h"
#include "QRScan.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            class IQRScanModule
            {
            public:
                virtual ~IQRScanModule() { }

                virtual IQRScanViewModel& GetQRScanViewModel() const = 0;

                virtual OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
            };
        }
    }
}
