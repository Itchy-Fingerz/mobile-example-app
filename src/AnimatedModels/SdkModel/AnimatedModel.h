// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "Positioning.h"
#include "AnimatedModels.h"
#include "IAnimatedModel.h"
#include "LatLongAltitude.h"

#include <vector>

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
                              float scale,
                              const std::vector<int>& visibleFloorIds);

                ~AnimatedModel();

                void Update(float dt) override;
                void Show() override;
                void Hide() override;
                bool IsIndoor() const override;
                Eegeo::Resources::Interiors::InteriorId GetIndoorMapId() const override;
                int GetIndoorMapFloorId() const override;
                const std::vector<int>& GetVisibleFloorIds() const override;

            private:
                void UpdatePosition();

                Eegeo::Rendering::SceneModels::SceneModel* m_pModel;
                Eegeo::Positioning::IPointOnMap* m_pPointOnMap;
                const Eegeo::Positioning::IPositioningViewComponent& m_positioningViewComponent;
                Eegeo::Rendering::Filters::SceneModelRenderableFilter& m_renderableFilter;

                Eegeo::Rendering::SceneModels::SceneModelAnimator* m_pModelAnimator;
                float m_absoluteHeadingDegrees;
                float m_scale;
                const std::vector<int> m_visibleFloorIds;

                bool m_isShowing;
            };
        }
    }
}
