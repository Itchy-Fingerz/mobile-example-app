// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "AnimatedModel.h"
#include "IPointOnMap.h"
#include "SceneModelAnimator.h"
#include "SceneModelRenderableFilter.h"
#include "SceneModelTransformHelpers.h"

#include "CameraHelpers.h"

namespace ExampleApp
{
    namespace AnimatedModels
    {
        namespace SdkModel
        {
            AnimatedModel::AnimatedModel(Eegeo::Rendering::SceneModels::SceneModel* pModel,
                                         Eegeo::Positioning::IPointOnMap* pPointOnMap,
                                         const Eegeo::Positioning::IPositioningViewComponent& positioningViewComponent,
                                         Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter,
                                         float absoluteHeadingDegrees,
                                         float scale)
            : m_pModel(pModel)
            , m_pPointOnMap(pPointOnMap)
            , m_positioningViewComponent(positioningViewComponent)
            , m_renderableFilter(renderableFilter)
            , m_absoluteHeadingDegrees(absoluteHeadingDegrees)
            , m_scale(scale)
            , m_isShowing(false)
            {
                UpdatePosition();

                m_pModelAnimator = new Eegeo::Rendering::SceneModels::SceneModelAnimator(*m_pModel, MODEL_ANIMATION_FPS);
                m_pModelAnimator->Play();

                if (!m_pPointOnMap->IsIndoor())
                {
                    Show();
                }
            }

            AnimatedModel::~AnimatedModel()
            {
                Hide();

                Eegeo_DELETE m_pModelAnimator;
                Eegeo_DELETE m_pModel;
                Eegeo_DELETE m_pPointOnMap;
            }

            void AnimatedModel::Show()
            {
                if (!m_isShowing)
                {
                    m_renderableFilter.AddSceneModel(*m_pModel);
                    m_isShowing = true;
                }
            }

            void AnimatedModel::Hide()
            {
                if (m_isShowing)
                {
                    m_renderableFilter.RemoveSceneModel(*m_pModel);
                    m_isShowing = false;
                }
            }

            void AnimatedModel::Update(float dt)
            {
                UpdateVisibility();
                if (!m_isShowing)
                {
                    return;
                }

                UpdatePosition();
                m_pModelAnimator->Update(dt);
            }

            void AnimatedModel::UpdateVisibility()
            {
                if (m_pPointOnMap->IsIndoor())
                {
                    if (m_positioningViewComponent.IsSelectedIndoorMapFloor(m_pPointOnMap->GetIndoorMapId(), m_pPointOnMap->GetDerivedIndoorMapFloorIndex()))
                    {
                        Show();
                    }
                    else
                    {
                        Hide();
                    }
                }
            }

            void AnimatedModel::UpdatePosition()
            {
                const Eegeo::Space::LatLongAltitude& untransformedPosition = m_pPointOnMap->GetDerivedCoordinate();
                auto ecefOrigin = m_positioningViewComponent.CalculateTransformedPoint(m_pPointOnMap->GetIndoorMapId(),
                                                                                       m_pPointOnMap->GetDerivedIndoorMapFloorIndex(),
                                                                                       untransformedPosition.ToECEF());
                Eegeo::m44 scaleMatrix;
                scaleMatrix.Scale(m_scale);
                Eegeo::Rendering::SceneModels::SceneModelTransformHelpers::PositionOnEarthSurface(*m_pModel,
                                                                                                  ecefOrigin,
                                                                                                  m_absoluteHeadingDegrees,
                                                                                                  scaleMatrix);
            }
        }
    }
}
