// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "AnimatedModels.h"
#include "LatLongAltitude.h"

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace AnimatedModels
    {
        namespace SdkModel
        {
            class IAnimatedModelsFactory
            {
            public:
                virtual ~IAnimatedModelsFactory() {}

                virtual IAnimatedModel* CreateAnimatedModel(const std::string& filename,
                                                            const Eegeo::Space::LatLongAltitude& latLongAltitude,
                                                            const std::string& indoorMapId,
                                                            int indoorMapFloorId,
                                                            const std::vector<int>& visibleFloorIds,
                                                            float absoluteHeadingDegrees,
                                                            float scale) = 0;
            };
        }
    }
}
