// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "PopUp.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            class IPopUpModule
            {
            public:
                virtual ~IPopUpModule() { }

                virtual IPopUpViewModel& GetPopUpViewModel() const = 0;
            };
        }
    }
}
