// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GlassRenderable.h"
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
            GlassRenderable::GlassRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                             const Eegeo::dv3& ecefPosition,
                                             const Eegeo::Rendering::Materials::IMaterial& material,
                                             const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                             Eegeo::Rendering::Mesh& mesh,
                                             bool depthTest,
                                             bool isReflection)
            : MaterialRenderableBase(layerId, ecefPosition, material, vertexBinding, mesh)
            , m_isReflection(isReflection)
            {
                
            }
            
            void GlassRenderable::OnMaterialChanged(const Eegeo::Rendering::Materials::IMaterial* pMaterial, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool)
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = vertexBindingPool.GetVertexBinding(m_mesh.GetVertexLayout(), GetMaterial()->GetShader().GetVertexAttributes());
                SetVertexBinding(vertexBinding);
            }
            
            void GlassRenderable::SetOrientationEcef(const Eegeo::m33& orientationEcef)
            {
                m_orientationEcef = orientationEcef.ToM44();
                Eegeo::m44::Inverse(m_inverseOrientationMatrix, m_orientationEcef);
            }
            
            void GlassRenderable::Render(Eegeo::Rendering::GLState& glState) const
            {
                m_material->SetStatePerRenderable(this, glState);
                
                m_mesh.BindVertexBuffers(GetVertexBinding(), glState);
                
                Eegeo_GL(glDrawElements(GL_TRIANGLES, m_mesh.GetNumOfIndices(), GL_UNSIGNED_SHORT, (void*)(0)));
                
                m_mesh.UnbindVertexBuffers(glState);
            }
            
            void GlassRenderable::UpdateMatrices(const Eegeo::dv3& ecefCameraPosition, const Eegeo::m44& viewProjection)
            {
                const Eegeo::v3& cameraRelativeModelOrigin = (GetEcefPosition() - ecefCameraPosition).ToSingle();
                
                if(!IsReflection())
                {
                    m_worldMatrix.SetFromBasis(m_orientationEcef.GetRow(0), m_orientationEcef.GetRow(1), m_orientationEcef.GetRow(2), cameraRelativeModelOrigin);
                    
                    m_worldRotationMatrix = m_orientationEcef;
                    m_inverseWorldRotationMatrix = m_inverseOrientationMatrix;
                    
                    Eegeo::m44 modelViewProjection;
                    Eegeo::m44::Mul(modelViewProjection, viewProjection, m_worldMatrix);
                    
                    SetModelViewProjection(modelViewProjection);
                    
                    m_eyePosition = Eegeo::v3::Zero();
                }
                else
                {
                    const Eegeo::v3& cameraRelativeModelOrigin = (GetEcefPosition() - ecefCameraPosition).ToSingle();
                    
                    m_worldMatrix.SetFromBasis(m_orientationEcef.GetRow(0), m_orientationEcef.GetRow(1), m_orientationEcef.GetRow(2), cameraRelativeModelOrigin);
                    
                    Eegeo::m44 reflectionMatrix;
                    MatrixHelpers::CreatePlanarReflectionMatrix(reflectionMatrix, (m_reflectionPlanePoint - ecefCameraPosition).ToSingle(), m_reflectionPlaneNormal);
                    
                    Eegeo::m44::Mul(m_worldMatrix, reflectionMatrix, m_worldMatrix);
                    
                    Eegeo::m44::Mul(m_worldRotationMatrix, reflectionMatrix, m_orientationEcef);
                    Eegeo::m44::Mul(m_inverseWorldRotationMatrix, reflectionMatrix, m_inverseOrientationMatrix);
                    
                    Eegeo::m44 modelViewProjection;
                    Eegeo::m44::Mul(modelViewProjection, viewProjection, m_worldMatrix);
                    
                    SetModelViewProjection(modelViewProjection);
                    
                    m_eyePosition = Eegeo::v3::Mul(-cameraRelativeModelOrigin, reflectionMatrix);
                    m_eyePosition = Eegeo::v3::Mul(m_eyePosition, m_worldRotationMatrix);
                }
            }
            
            void GlassRenderable::SetReflectionPlane(const Eegeo::dv3& planePoint, const Eegeo::v3& planeNormal)
            {
                m_reflectionPlanePoint = planePoint;
                m_reflectionPlaneNormal = planeNormal;
            }
            
            const Eegeo::m44& GlassRenderable::GetWorldMatrix() const
            {
                return m_worldMatrix;
            }
            
            const Eegeo::m44& GlassRenderable::GetWorldRotationMatrix() const
            {
                return m_worldRotationMatrix;
            }
            
            const Eegeo::m44& GlassRenderable::GetInverseWorldRotationMatrix() const
            {
                return m_inverseWorldRotationMatrix;
            }
            
            const Eegeo::v3& GlassRenderable::GetEyePosition() const
            {
                return m_eyePosition;
            }
        }
    }
}