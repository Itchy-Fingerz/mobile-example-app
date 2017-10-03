// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace View
        {
            class ICustomAlertViewModule
            {
            public:

                virtual ~ICustomAlertViewModule() { }

                virtual CustomAlertView& GetCustomAlertView() const = 0;
                virtual CustomAlertController& GetCustomAlertController() const = 0;
            };
        }
    }
}
