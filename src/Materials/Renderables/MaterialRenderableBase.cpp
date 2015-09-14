// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MaterialRenderableBase.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Renderables
        {
            MaterialRenderableBase::MaterialRenderableBase(Eegeo::Rendering::LayerIds::Values layerId,
                                                           const Eegeo::dv3& ecefPosition,
                                                           const Eegeo::Rendering::Materials::IMaterial& material,
                                                           const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                                           Eegeo::Rendering::Mesh& mesh)
            : Eegeo::Rendering::RenderableBase(layerId, ecefPosition, &material, vertexBinding)
            , m_mesh(mesh)
            , m_orientationEcef(Eegeo::m44::CreateIdentity())
            , m_rotationMatrix(Eegeo::m44::CreateIdentity())
            {
                
            }
            
            void MaterialRenderableBase::SetOrientationEcef(const Eegeo::m33& orientationEcef)
            {
                m_orientationEcef = orientationEcef.ToM44();
            }
            
            void MaterialRenderableBase::SetRotationMatrix(const Eegeo::m33& rotationMatrix)
            {
                m_rotationMatrix = rotationMatrix.ToM44();
            }
        }
    }
}