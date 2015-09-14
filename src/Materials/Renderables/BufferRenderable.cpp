// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BufferRenderable.h"
#include "Mesh.h"
#include "VertexBindingPool.h"
#include "IMaterial.h"
#include "Shader.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Renderables
        {
            BufferRenderable::BufferRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                               const Eegeo::dv3& ecefPosition,
                                               const Eegeo::Rendering::Materials::IMaterial& material,
                                               const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                               Eegeo::Rendering::Mesh& mesh)
            : MaterialRenderableBase(layerId, ecefPosition, material, vertexBinding, mesh)
            {
                
            }
            
            void BufferRenderable::OnMaterialChanged(const Eegeo::Rendering::Materials::IMaterial* pMaterial, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool)
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = vertexBindingPool.GetVertexBinding(m_mesh.GetVertexLayout(), GetMaterial()->GetShader().GetVertexAttributes());
                SetVertexBinding(vertexBinding);
            }
            
            void BufferRenderable::Render(Eegeo::Rendering::GLState& glState) const
            {
                m_material->SetStatePerRenderable(this, glState);
                
                m_mesh.BindVertexBuffers(GetVertexBinding(), glState);
                
                Eegeo_GL(glDrawElements(GL_TRIANGLES, m_mesh.GetNumOfIndices(), GL_UNSIGNED_SHORT, (void*)(0)));
                
                m_mesh.UnbindVertexBuffers(glState);
            }
            
            void BufferRenderable::UpdateMatrices(const Eegeo::dv3& ecefCameraPosition, const Eegeo::m44& viewProjection)
            {
                const Eegeo::v3& cameraRelativeModelOrigin = (GetEcefPosition() - ecefCameraPosition).ToSingle();
                
                Eegeo::m44 modelMatrix;
                modelMatrix.SetFromBasis(m_orientationEcef.GetRow(0), m_orientationEcef.GetRow(1), m_orientationEcef.GetRow(2), cameraRelativeModelOrigin);
                
                Eegeo::m44 modelViewProjection;
                Eegeo::m44::Mul(modelViewProjection, viewProjection, modelMatrix);
                
                SetModelViewProjection(modelViewProjection);
            }
        }
    }
}