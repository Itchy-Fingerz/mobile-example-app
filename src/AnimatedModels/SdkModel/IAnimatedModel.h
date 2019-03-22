// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace AnimatedModels
    {
        namespace SdkModel
        {
            class IAnimatedModel
            {
            public:
                virtual ~IAnimatedModel(){}

                virtual void Update(float dt) = 0;
            };
        }
    }
}
