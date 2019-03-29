// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ThreeSixtyInteractionViewIncludes.h"
#include "ThreeSixtyInteractionController.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            class IThreeSixtyInteractionViewModule
            {
            public:
                virtual ~IThreeSixtyInteractionViewModule() { }

                virtual ThreeSixtyInteractionController& GetThreeSixtyInteractionController() const = 0;

                virtual ThreeSixtyInteractionView& GetThreeSixtyInteractionView() const = 0;
            };
        }
    }
}
