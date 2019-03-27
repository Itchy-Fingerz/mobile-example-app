// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "AnimatedModels.h"
#include "LatLongAltitude.h"
#include "Positioning.h"
#include "Interiors.h"
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
                AnimatedModelsController(IAnimatedModelsFactory& animatedModelsFactory,
                                         const Eegeo::Positioning::IPositioningViewComponent& positioningViewComponent,
                                         const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);

                ~AnimatedModelsController();

                void Update(float dt) override;

                void LoadModel(const std::string& filename,
                               const Eegeo::Space::LatLongAltitude& latLongAltitude,
                               const std::string& indoorMapId,
                               int indoorMapFloorId,
                               const std::vector<int>& visibleFloorIds,
                               float absoluteHeadingDegrees,
                               float scale) override;

            private:
                void UpdateVisibility(IAnimatedModel& model);

                IAnimatedModelsFactory& m_animatedModelsFactory;
                const Eegeo::Positioning::IPositioningViewComponent& m_positioningViewComponent;
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                std::vector<IAnimatedModel*> m_models;
            };
        }
    }
}
