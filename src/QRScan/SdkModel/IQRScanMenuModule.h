// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace SdkModel
        {
            class IQRScanMenuModule
            {
            public:
                virtual ~IQRScanMenuModule() { }

                virtual Menu::View::IMenuModel& GetQRScanMenuModel() const = 0;
            };
        }
    }
}
