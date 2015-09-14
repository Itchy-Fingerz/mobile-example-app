// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MaterialRenderableBase.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Renderables
        {
            class GlassRenderable : public MaterialRenderableBase
            {
            public:
                GlassRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                const Eegeo::dv3& ecefPosition,
                                const Eegeo::Rendering::Materials::IMaterial& material,
                                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                Eegeo::Rendering::Mesh& mesh,
                                bool depthTest,
                                bool isReflection);
                
                void UpdateMatrices(const Eegeo::dv3& ecefCameraPosition, const Eegeo::m44& viewProjection);
                
                void SetReflectionPlane(const Eegeo::dv3& planePoint, const Eegeo::v3& planeNormal);
                
                void Render(Eegeo::Rendering::GLState& glState) const;
                
                void OnMaterialChanged(const Eegeo::Rendering::Materials::IMaterial* pMaterial, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool);
                
                void SetOrientationEcef(const Eegeo::m33& orientationEcef);
                
                bool IsReflection() const { return m_isReflection; }
                
                const Eegeo::m44& GetWorldMatrix() const;
                const Eegeo::m44& GetWorldRotationMatrix() const;
                const Eegeo::m44& GetInverseWorldRotationMatrix() const;
                const Eegeo::v3& GetEyePosition() const;
                
            private:
                Eegeo::m44 m_inverseOrientationMatrix;
                Eegeo::m44 m_worldMatrix;
                Eegeo::m44 m_worldRotationMatrix;
                Eegeo::m44 m_inverseWorldRotationMatrix;
                Eegeo::v3 m_eyePosition;
                bool m_isReflection;
                Eegeo::dv3 m_reflectionPlanePoint;
                Eegeo::v3 m_reflectionPlaneNormal;
            };
        }
    }
}