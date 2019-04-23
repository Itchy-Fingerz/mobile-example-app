// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"

#include "VectorMath.h"
#include <vector>
#include <unordered_map>

namespace ExampleApp
{
    namespace VenueLabels
    {
        namespace SdkModel
        {
            class IVenueLabelsController
            {
            public:
                
                virtual ~IVenueLabelsController() {}
                virtual void AddVenueLabels() = 0;
                virtual void ShowLabels(bool visible) = 0;
                virtual void Update(float dt) = 0;
                virtual bool HandleTouchTap(const Eegeo::v2& screenTapPoint) = 0;
                
            };
        }
    }
}
