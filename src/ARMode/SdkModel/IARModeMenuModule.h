// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Menu.h"

namespace ExampleApp
{
    namespace ARMode
    {
        namespace SdkModel
        {
            class IARModeMenuModule
            {
            public:
                virtual ~IARModeMenuModule() { }

                virtual Menu::View::IMenuModel& GetARModeMenuModel() const = 0;
            };
        }
    }
}
