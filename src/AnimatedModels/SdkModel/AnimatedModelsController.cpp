// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "AnimatedModelsController.h"
#include "AnimatedModelsFactory.h"
#include "IAnimatedModel.h"
#include "IPositioningViewComponent.h"
#include "InteriorInteractionModel.h"
#include "InteriorsFloorModel.h"
#include "InteriorsModel.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace AnimatedModels
    {
        namespace SdkModel
        {
            AnimatedModelsController::AnimatedModelsController(IAnimatedModelsFactory& animatedModelsFactory,
                                                               const Eegeo::Positioning::IPositioningViewComponent& positioningViewComponent,
                                                               const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
            : m_animatedModelsFactory(animatedModelsFactory)
            , m_positioningViewComponent(positioningViewComponent)
            , m_interiorInteractionModel(interiorInteractionModel)
            {}

            AnimatedModelsController::~AnimatedModelsController()
            {
                for (auto model : m_models)
                {
                    Eegeo_DELETE model;
                }
            }

            void AnimatedModelsController::Update(float dt)
            {
                for (auto model : m_models)
                {
                    UpdateVisibility(*model);
                    model->Update(dt);
                }
            }

            void AnimatedModelsController::LoadModel(const std::string& filename,
                                                     const Eegeo::Space::LatLongAltitude& latLongAltitude,
                                                     const std::string& indoorMapId,
                                                     int indoorMapFloorId,
                                                     const std::vector<int>& visibleFloorIds,
                                                     float absoluteHeadingDegrees,
                                                     float scale)
            {
                auto model = m_animatedModelsFactory.CreateAnimatedModel(filename,
                                                                         latLongAltitude,
                                                                         indoorMapId,
                                                                         indoorMapFloorId,
                                                                         visibleFloorIds,
                                                                         absoluteHeadingDegrees,
                                                                         scale);
                m_models.push_back(model);
            }

            void AnimatedModelsController::UpdateVisibility(IAnimatedModel& model)
            {
                if (m_positioningViewComponent.GetMapViewMode() == Eegeo::MapLayers::MapViewMode::Type::Outdoor && (!model.IsIndoor()))
                {
                    model.Show();
                    return;
                }

                if (m_positioningViewComponent.GetMapViewMode() == Eegeo::MapLayers::MapViewMode::Type::Indoor && model.IsIndoor())
                {
                    if (!m_positioningViewComponent.IsSelectedIndoorMap(model.GetIndoorMapId()) || !m_interiorInteractionModel.IsCollapsed())
                    {
                        model.Hide();
                        return;
                    }

                    const auto* pSelectedFloorModel = m_interiorInteractionModel.GetSelectedFloorModel();
                    if (pSelectedFloorModel == NULL)
                    {
                        model.Hide();
                        return;
                    }

                    const int currentFloorId = pSelectedFloorModel->GetFloorNumber();
                    const auto& visibleFloorIds = model.GetVisibleFloorIds();
                    if (std::find(visibleFloorIds.begin(), visibleFloorIds.end(), currentFloorId) != visibleFloorIds.end())
                    {
                        model.Show();
                        return;
                    }
                }

                model.Hide();
            }
        }
    }
}
