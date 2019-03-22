// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "AnimatedModels.h"
#include "LatLongAltitude.h"
#include "Positioning.h"
#include "IAnimatedModelsFactory.h"

#include <string>

namespace ExampleApp
{
    namespace AnimatedModels
    {
        namespace SdkModel
        {
            class AnimatedModelsFactory : public IAnimatedModelsFactory, private Eegeo::NonCopyable
            {
            public:
                AnimatedModelsFactory(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                      Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter,
                                      Eegeo::Positioning::IPointOnMapFactory& pointOnMapFactory,
                                      const Eegeo::Positioning::IPositioningViewComponent& positioningViewComponent);

                ~AnimatedModelsFactory() {}

                IAnimatedModel* CreateAnimatedModel(const std::string& filename,
                                                    const Eegeo::Space::LatLongAltitude& latLongAltitude,
                                                    const std::string& indoorMapId,
                                                    int indoorMapFloorId,
                                                    float absoluteHeadingDegrees,
                                                    float scale) override;

            private:
                Eegeo::Rendering::SceneModels::SceneModelLoader& m_sceneModelLoader;
                Eegeo::Rendering::Filters::SceneModelRenderableFilter& m_renderableFilter;
                Eegeo::Positioning::IPointOnMapFactory& m_pointOnMapFactory;
                const Eegeo::Positioning::IPositioningViewComponent& m_positioningViewComponent;
            };
        }
    }
}
