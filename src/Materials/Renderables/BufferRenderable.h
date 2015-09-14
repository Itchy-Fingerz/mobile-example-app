// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MaterialRenderableBase.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Renderables
        {
            class BufferRenderable : public MaterialRenderableBase
            {
            public:
                BufferRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                 const Eegeo::dv3& ecefPosition,
                                 const Eegeo::Rendering::Materials::IMaterial& material,
                                 const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                 Eegeo::Rendering::Mesh& mesh);
                
                void UpdateMatrices(const Eegeo::dv3& ecefCameraPosition, const Eegeo::m44& viewProjection);
                
                void Render(Eegeo::Rendering::GLState& glState) const;
                
                void OnMaterialChanged(const Eegeo::Rendering::Materials::IMaterial* pMaterial, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool);
                
            private:
            };
        }
    }
}