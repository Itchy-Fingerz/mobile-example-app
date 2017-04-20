// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "CustomAlert.h"
#include "ScreenControlViewModelIncludes.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace SdkModel
        {
            class ICustomAlertModule
            {
            public:
                virtual ~ICustomAlertModule() { }
                
                virtual View::ICustomAlertViewModel& GetCustomAlertViewModel() const = 0;
                
                virtual ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const = 0;
                                
            };
        }
    }
}
