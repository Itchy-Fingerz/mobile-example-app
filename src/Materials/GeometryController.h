// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IGeometryController.h"
#include "MaterialsIncludes.h"
#include "Types.h"
#include "Rendering.h"
#include "Modules.h"
#include "DebugRendering.h"
#include "LatLongAltitude.h"
#include <vector>

namespace ExampleApp
{
    namespace Materials
    {
        class GeometryController : public IGeometryController, protected Eegeo::NonCopyable
        {
        public:
            GeometryController(MaterialStore& materialStore,
                               MaterialRenderableFilter& renderableFilter,
                               Eegeo::Modules::Core::RenderingModule& renderingModule,
                               const Eegeo::Space::LatLongAltitude& originLatLongAltitude,
                               Eegeo::DebugRendering::DebugRenderer& debugRenderer);
            
            ~GeometryController();
            
            void Update(float dt);
            
        private:
            typedef std::vector<Renderables::MaterialRenderableBase*> MaterialRenderableVector;
            typedef std::vector<Eegeo::Rendering::Mesh*> MeshVector;
            
            void CreateReflectiveFloor();
            void CreateGlassPlanes();
            void CreateChromeObjects();
            void CreateAdditionalGeometry();
            
            const bool m_showDebugAxes;
            
            const MaterialStore& m_materialStore;
            MaterialRenderableFilter& m_renderableFilter;
            Eegeo::Modules::Core::RenderingModule& m_renderingModule;
            
            Eegeo::Rendering::VertexLayouts::VertexLayout* m_pPositionNormalUvVertexLayout;
            
            MaterialRenderableVector m_renderables;
            MeshVector m_meshes;
            
            MaterialRenderableVector m_rotatingRenderables;
            float m_currentRotation;
            
            Eegeo::Space::LatLongAltitude m_originLatLongAltitude;
            Eegeo::dv3 m_centrePosition;
            Eegeo::m33 m_basisToEcef;
            
            Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
        };
    }
}