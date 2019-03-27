// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "AnimatedModelsModule.h"
#include "AnimatedModelsFactory.h"
#include "AnimatedModelsController.h"
#include "AnimatedModel.h"

namespace ExampleApp
{
    namespace AnimatedModels
    {
        namespace SdkModel
        {
            AnimatedModelsModule::AnimatedModelsModule(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                                       Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter,
                                                       Eegeo::Positioning::IPointOnMapFactory& pointOnMapFactory,
                                                       const Eegeo::Positioning::IPositioningViewComponent& positioningViewComponent,
                                                       const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                       const std::vector<ExampleApp::ApplicationConfig::SdkModel::AnimatedModelsConfig>& animatedModelsConfig)
            {
                m_pAnimatedModelsFactory = Eegeo_NEW(AnimatedModelsFactory)(sceneModelLoader, renderableFilter, pointOnMapFactory, positioningViewComponent);
                m_pAnimatedModelsController = Eegeo_NEW(AnimatedModelsController)(*m_pAnimatedModelsFactory, positioningViewComponent, interiorInteractionModel);

                for (const auto& modelInfo : animatedModelsConfig)
                {
                    m_pAnimatedModelsController->LoadModel(modelInfo.filename,
                                                           Eegeo::Space::LatLongAltitude::FromDegrees(modelInfo.latitudeInDegrees, modelInfo.longitudeInDegrees, modelInfo.altitudeInMetres),
                                                           modelInfo.indoorMapId,
                                                           modelInfo.indoorMapFloorId,
                                                           modelInfo.visibleIndoorMapFloorIds,
                                                           modelInfo.absoluteHeadingDegrees,
                                                           modelInfo.scale);
                }
            }

            AnimatedModelsModule::~AnimatedModelsModule()
            {
                delete m_pAnimatedModelsController;
                delete m_pAnimatedModelsFactory;
            }

            void AnimatedModelsModule::Update(float dt)
            {
                m_pAnimatedModelsController->Update(dt);
            }
        }
    }
}
