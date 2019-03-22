// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "AnimatedModels.h"
#include "LatLongAltitude.h"
#include "IAnimatedModelsController.h"

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace AnimatedModels
    {
        namespace SdkModel
        {
            class AnimatedModelsController : public IAnimatedModelsController, private Eegeo::NonCopyable
            {
            public:
                AnimatedModelsController(IAnimatedModelsFactory& animatedModelsFactory);

                ~AnimatedModelsController();

                void Update(float dt) override;

                void LoadModel(const std::string& filename,
                               const Eegeo::Space::LatLongAltitude& latLongAltitude,
                               const std::string& indoorMapId,
                               int indoorMapFloorId,
                               float absoluteHeadingDegrees,
                               float scale) override;

            private:
                IAnimatedModelsFactory& m_animatedModelsFactory;
                std::vector<IAnimatedModel*> m_models;
            };
        }
    }
}
