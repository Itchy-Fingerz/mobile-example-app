// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "Interiors.h"

#include <vector>

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

                virtual void Show() = 0;

                virtual void Hide() = 0;

                virtual bool IsIndoor() const = 0;

                virtual Eegeo::Resources::Interiors::InteriorId GetIndoorMapId() const = 0;

                virtual int GetIndoorMapFloorId() const = 0;

                virtual const std::vector<int>& GetVisibleFloorIds() const = 0;
            };
        }
    }
}
