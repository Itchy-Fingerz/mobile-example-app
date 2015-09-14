// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LitRenderable.h"
#include "Mesh.h"
#include "VertexBindingPool.h"
#include "IMaterial.h"
#include "Shader.h"
#include "MatrixHelpers.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Renderables
        {
            LitRenderable::LitRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                         const Eegeo::dv3& ecefPosition,
                                         const Eegeo::Rendering::Materials::IMaterial& material,
                                         const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                         Eegeo::Rendering::Mesh& mesh,
                                         bool depthTest,
                                         bool alphaBlend,
                                         bool isReflection)
            : MaterialRenderableBase(layerId, ecefPosition, material, vertexBinding, mesh)
            , m_depthTest(depthTest)
            , m_alphaBlend(alphaBlend)
            , m_isReflection(isReflection)
            {
                
            }
            
            void LitRenderable::OnMaterialChanged(const Eegeo::Rendering::Materials::IMaterial* pMaterial, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool)
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = vertexBindingPool.GetVertexBinding(m_mesh.GetVertexLayout(), GetMaterial()->GetShader().GetVertexAttributes());
                SetVertexBinding(vertexBinding);
            }
            
            void LitRenderable::SetOrientationEcef(const Eegeo::m33& orientationEcef)
            {
                m_orientationEcef = orientationEcef.ToM44();
            }
            
            void LitRenderable::Render(Eegeo::Rendering::GLState& glState) const
            {
                m_material->SetStatePerRenderable(this, glState);
                
                m_mesh.BindVertexBuffers(GetVertexBinding(), glState);
                
                Eegeo_GL(glDrawElements(GL_TRIANGLES, m_mesh.GetNumOfIndices(), GL_UNSIGNED_SHORT, (void*)(0)));
                
                m_mesh.UnbindVertexBuffers(glState);
            }
            
            void LitRenderable::UpdateMatrices(const Eegeo::dv3& ecefCameraPosition, const Eegeo::m44& viewProjection)
            {
                const Eegeo::v3& cameraRelativeModelOrigin = (GetEcefPosition() - ecefCameraPosition).ToSingle();
                
                Eegeo::m44::Mul(m_worldRotationMatrix, m_rotationMatrix, m_orientationEcef);
                
                m_worldMatrix.SetFromBasis(m_worldRotationMatrix.GetRow(0), m_worldRotationMatrix.GetRow(1), m_worldRotationMatrix.GetRow(2), cameraRelativeModelOrigin);
                
                if(IsReflection())
                {
                    Eegeo::m44 reflectionMatrix;
                    MatrixHelpers::CreatePlanarReflectionMatrix(reflectionMatrix, (m_reflectionPlanePoint - ecefCameraPosition).ToSingle(), m_reflectionPlaneNormal);
                    
                    Eegeo::m44::Mul(m_worldMatrix, reflectionMatrix, m_worldMatrix);
                    
                    Eegeo::m44::Mul(m_worldRotationMatrix, reflectionMatrix, m_worldRotationMatrix);
                }
                
                Eegeo::m44 modelViewProjection;
                Eegeo::m44::Mul(modelViewProjection, viewProjection, m_worldMatrix);
                
                SetModelViewProjection(modelViewProjection);
                
                Eegeo::m44::Inverse(m_inverseTransposeWorldMatrix, m_worldMatrix);
            }
            
            void LitRenderable::SetReflectionPlane(const Eegeo::dv3& planePoint, const Eegeo::v3& planeNormal)
            {
                m_reflectionPlanePoint = planePoint;
                m_reflectionPlaneNormal = planeNormal;
            }
            
            const Eegeo::m44& LitRenderable::GetWorldMatrix() const
            {
                return m_worldMatrix;
            }
            
            const Eegeo::m44& LitRenderable::GetWorldRotationMatrix() const
            {
                return m_worldRotationMatrix;
            }
            
            const Eegeo::m44& LitRenderable::GetInverseTransposeModelMatrix() const
            {
                return m_inverseTransposeWorldMatrix;
            }
        }
    }
}