// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "AnimatedModelsController.h"
#include "AnimatedModelsFactory.h"
#include "IAnimatedModel.h"

namespace ExampleApp
{
    namespace AnimatedModels
    {
        namespace SdkModel
        {
            AnimatedModelsController::AnimatedModelsController(IAnimatedModelsFactory& animatedModelsFactory)
            : m_animatedModelsFactory(animatedModelsFactory)
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
                    model->Update(dt);
                }
            }

            void AnimatedModelsController::LoadModel(const std::string& filename,
                                                     const Eegeo::Space::LatLongAltitude& latLongAltitude,
                                                     const std::string& indoorMapId,
                                                     int indoorMapFloorId,
                                                     float absoluteHeadingDegrees,
                                                     float scale)
            {
                auto model = m_animatedModelsFactory.CreateAnimatedModel(filename, latLongAltitude, indoorMapId, indoorMapFloorId, absoluteHeadingDegrees, scale);
                m_models.push_back(model);
            }
        }
    }
}
