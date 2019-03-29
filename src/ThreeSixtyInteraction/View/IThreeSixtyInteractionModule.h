// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IOpenableControlViewModel.h"
#include "ThreeSixtyInteraction.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            class IThreeSixtyInteractionModule
            {
            public:
                virtual ~IThreeSixtyInteractionModule() { }

                virtual IThreeSixtyInteractionViewModel& GetThreeSixtyInteractionViewModel() const = 0;
                
                virtual OpenableControl::View::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
            };
        }
    }
}
