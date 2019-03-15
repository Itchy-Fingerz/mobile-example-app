// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include <string>

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            class IPopUpView
            {
            public:
                virtual ~IPopUpView() { };
                virtual void Open(double x, double y) = 0;
                virtual void Close() = 0;
            };
        }
    }
}
