// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "Rendering.h"
#include "Positioning.h"
#include "AnimatedModels.h"
#include "AnimatedModelsConfig.h"

namespace ExampleApp
{
    namespace AnimatedModels
    {
        namespace SdkModel
        {
            class AnimatedModelsModule : private Eegeo::NonCopyable
            {
            public:
                AnimatedModelsModule(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                     Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter,
                                     Eegeo::Positioning::IPointOnMapFactory& pointOnMapFactory,
                                     const Eegeo::Positioning::IPositioningViewComponent& positioningViewComponent,
                                     const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                     const std::vector<ExampleApp::ApplicationConfig::SdkModel::AnimatedModelsConfig>& animatedModelsConfig);

                ~AnimatedModelsModule();

                void Update(float dt);

            private:
                IAnimatedModelsFactory* m_pAnimatedModelsFactory;
                IAnimatedModelsController* m_pAnimatedModelsController;
            };
        }
    }
}
