// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "Positioning.h"
#include "AnimatedModels.h"
#include "IAnimatedModel.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace AnimatedModels
    {
        namespace SdkModel
        {
            class AnimatedModel : public IAnimatedModel, private Eegeo::NonCopyable
            {
            public:
                AnimatedModel(Eegeo::Rendering::SceneModels::SceneModel* pModel,
                              Eegeo::Positioning::IPointOnMap* pPointOnMap,
                              const Eegeo::Positioning::IPositioningViewComponent& positioningViewComponent,
                              Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter,
                              float absoluteHeadingDegrees,
                              float scale);

                ~AnimatedModel();

                void Update(float dt) override;

            private:
                void Show();
                void Hide();
                void UpdateVisibility();
                void UpdatePosition();

                Eegeo::Rendering::SceneModels::SceneModel* m_pModel;
                Eegeo::Positioning::IPointOnMap* m_pPointOnMap;
                const Eegeo::Positioning::IPositioningViewComponent& m_positioningViewComponent;
                Eegeo::Rendering::Filters::SceneModelRenderableFilter& m_renderableFilter;

                Eegeo::Rendering::SceneModels::SceneModelAnimator* m_pModelAnimator;
                float m_absoluteHeadingDegrees;
                float m_scale;

                bool m_isShowing;
            };
        }
    }
}
