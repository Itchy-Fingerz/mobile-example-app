// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "PopUpViewIncludes.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            class IPopUpViewModule
            {
            public:
                virtual ~IPopUpViewModule() { }

                virtual PopUpView& GetPopUpView() const = 0;
            };
        }
    }
}
