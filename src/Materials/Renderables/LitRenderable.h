// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MaterialRenderableBase.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Renderables
        {
            class LitRenderable : public MaterialRenderableBase
            {
            public:
                LitRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                              const Eegeo::dv3& ecefPosition,
                              const Eegeo::Rendering::Materials::IMaterial& material,
                              const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                              Eegeo::Rendering::Mesh& mesh,
                              bool depthTest,
                              bool alphaBlend,
                              bool isReflection);
                
                void UpdateMatrices(const Eegeo::dv3& ecefCameraPosition, const Eegeo::m44& viewProjection);
                
                void SetReflectionPlane(const Eegeo::dv3& planePoint, const Eegeo::v3& planeNormal);

                void Render(Eegeo::Rendering::GLState& glState) const;
                
                void OnMaterialChanged(const Eegeo::Rendering::Materials::IMaterial* pMaterial, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool);
                
                void SetOrientationEcef(const Eegeo::m33& orientationEcef);
                
                void SetDepthTest(bool enabled) { m_depthTest = enabled; }
                void SetAlphaBlend(bool enabled) { m_alphaBlend = enabled; }
                
                bool IsDepthTest() const { return m_depthTest; }
                bool IsAlphaBlend() const { return m_alphaBlend; }
                bool IsReflection() const { return m_isReflection; }
                
                const Eegeo::m44& GetWorldMatrix() const;
                const Eegeo::m44& GetWorldRotationMatrix() const;
                const Eegeo::m44& GetInverseTransposeModelMatrix() const;
                
            protected:
                Eegeo::m44 m_worldMatrix;
                Eegeo::m44 m_worldRotationMatrix;
                Eegeo::m44 m_inverseTransposeWorldMatrix;
                bool m_depthTest;
                bool m_alphaBlend;
                bool m_isReflection;
                Eegeo::dv3 m_reflectionPlanePoint;
                Eegeo::v3 m_reflectionPlaneNormal;
            };
        }
    }
}