// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "IVenueLabelsController.h"

namespace ExampleApp
{
    namespace VenueLabels
    {
        namespace SdkModel
        {
            class IVenueLabelsModule
            {
            public:
                virtual ~IVenueLabelsModule() { }
                virtual void Update(float dt) = 0;
                virtual IVenueLabelsController& GetVenueLabelController() = 0;
            };
        }
    }
}
