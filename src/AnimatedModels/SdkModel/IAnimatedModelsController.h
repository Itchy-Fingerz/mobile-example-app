// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

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
            class IAnimatedModelsController
            {
            public:
                virtual ~IAnimatedModelsController() {}

                virtual void Update(float dt) = 0;

                virtual void LoadModel(const std::string& filename,
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
