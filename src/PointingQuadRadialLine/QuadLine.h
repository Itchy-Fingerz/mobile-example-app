// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IRenderableFilter.h"
#include "Rendering.h"
#include "Modules.h"
#include "Helpers.h"
#include "IAppCameraController.h"
#include <vector>
#include "DebugRenderer.h"

namespace ExampleApp
{
    namespace PointingQuadRadialLine
    {
        class QuadLineRenderable;
        class QuadLineMeshUnlitColorMaterial;
        
        
        
        class QuadLine : public Eegeo::Rendering::IRenderableFilter
        {
        public:
            typedef std::vector<QuadLineRenderable*> ExampleMeshRenderableVector;
            
            QuadLine(Eegeo::Modules::Core::RenderingModule& renderingModule,
                        Eegeo::DebugRendering::DebugRenderer &debugRenderer,
                        Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                        Eegeo::v4 quadColor,
                        Eegeo::dv3 fromEcef,
                        Eegeo::dv3 toEcef,
                        float tileLength,
                        float thickness);
            
            virtual ~QuadLine();
            
            void Start();
            void Update(float dt);
            
            void Draw() {}
            void Suspend() {}
            
            // IRenderableFilter interface
            void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
            
        private:            
            
            int currentStep;
            Eegeo::Modules::Core::RenderingModule& m_renderingModule;
            Eegeo::DebugRendering::DebugRenderer& m_debugRenderer;
            Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
            Eegeo::v4 m_quadColor;
            
            Eegeo::Rendering::VertexLayouts::VertexLayout* m_pPositionUvVertexLayout;
            Eegeo::Rendering::Shaders::ColorShader* m_pShader;
            QuadLineMeshUnlitColorMaterial* m_pMaterial;
            Eegeo::Rendering::Mesh* m_pUnlitBoxMesh;
            QuadLineRenderable* m_pRenderable;
            
            Eegeo::dv3 m_fromEcef;
            Eegeo::dv3 m_toEcef;
            float m_tileLength;
            float m_thickness;
            
            void DrawQuadLine();
            Eegeo::m33 GetLookAtOrientationMatrix(const Eegeo::v3& targetPosition, const Eegeo::v3& objectPosition, Eegeo::v3 up);
            
        };
    }
}
