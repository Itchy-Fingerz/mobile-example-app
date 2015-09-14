// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "RenderableBase.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Renderables
        {
            class MaterialRenderableBase : public Eegeo::Rendering::RenderableBase
            {
            public:
                MaterialRenderableBase(Eegeo::Rendering::LayerIds::Values layerId,
                                       const Eegeo::dv3& ecefPosition,
                                       const Eegeo::Rendering::Materials::IMaterial& material,
                                       const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                       Eegeo::Rendering::Mesh& mesh);
                
                virtual ~MaterialRenderableBase() { }
                
                virtual void UpdateMatrices(const Eegeo::dv3& ecefCameraPosition, const Eegeo::m44& viewProjection) = 0;
                
                virtual void SetOrientationEcef(const Eegeo::m33& orientationEcef);
                
                void SetRotationMatrix(const Eegeo::m33& rotationMatrix);
            protected:
                Eegeo::Rendering::Mesh& m_mesh;
                Eegeo::m44 m_orientationEcef;
                Eegeo::m44 m_rotationMatrix;
            };
        }
    }
}