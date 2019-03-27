// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "AnimatedModelsFactory.h"
#include "AnimatedModel.h"
#include "SceneModelLoader.h"
#include "SceneModel.h"
#include "LayerIds.h"
#include "PointOnMapFactory.h"
#include "PointOnMapBuilder.h"
#include "IPointOnMap.h"

namespace ExampleApp
{
    namespace AnimatedModels
    {
        namespace SdkModel
        {

            AnimatedModelsFactory::AnimatedModelsFactory(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                                         Eegeo::Rendering::Filters::SceneModelRenderableFilter& renderableFilter,
                                                         Eegeo::Positioning::IPointOnMapFactory& pointOnMapFactory,
                                                         const Eegeo::Positioning::IPositioningViewComponent& positioningViewComponent)
            : m_sceneModelLoader(sceneModelLoader)
            , m_renderableFilter(renderableFilter)
            , m_pointOnMapFactory(pointOnMapFactory)
            , m_positioningViewComponent(positioningViewComponent)
            {}

            IAnimatedModel* AnimatedModelsFactory::CreateAnimatedModel(const std::string& filename,
                                                                       const Eegeo::Space::LatLongAltitude& latLongAltitude,
                                                                       const std::string& indoorMapId,
                                                                       int indoorMapFloorId,
                                                                       const std::vector<int>& visibleFloorIds,
                                                                       float absoluteHeadingDegrees,
                                                                       float scale)
            {
                Eegeo::Rendering::SceneModels::SceneModel* pModel = m_sceneModelLoader.LoadPOD(filename);

                Eegeo::Positioning::PointOnMapBuilder pointOnMapBuilder;
                pointOnMapBuilder.SetCoordinate(latLongAltitude.GetLatitudeInDegrees(), latLongAltitude.GetLongitudeInDegrees());
                pointOnMapBuilder.SetElevation(latLongAltitude.GetAltitude());
                pointOnMapBuilder.SetIndoorMap(indoorMapId, indoorMapFloorId);

                auto pPointOnMap = m_pointOnMapFactory.Create(pointOnMapBuilder.Build());

                if (pPointOnMap->IsIndoor())
                {
                    pModel->SetLayer(Eegeo::Rendering::LayerIds::Interiors);
                }
                else
                {
                    pModel->SetLayer(Eegeo::Rendering::LayerIds::AfterWorldTranslucency);
                }

                return Eegeo_NEW(AnimatedModel)(pModel,
                                                pPointOnMap,
                                                m_positioningViewComponent,
                                                m_renderableFilter,
                                                absoluteHeadingDegrees,
                                                scale,
                                                visibleFloorIds);
            }
        }
    }
}
