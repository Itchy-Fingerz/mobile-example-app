// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DiffuseSpecularMaterial.h"
#include "DiffuseSpecularShader.h"
#include "GlobalLighting.h"
#include "TextureMinifyType.h"
#include "GLHelpers.h"
#include "LitRenderable.h"
#include "StencilMapLayerMask.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Materials
        {
            DiffuseSpecularMaterial::DiffuseSpecularMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                                             const std::string& name,
                                                             Shaders::DiffuseSpecularShader& shader,
                                                             Eegeo::Rendering::TTextureId textureId,
                                                             float specularPower,
                                                             float specularIntensity,
                                                             const Eegeo::Lighting::GlobalLighting& globalLighting)
            : m_materialId(materialId)
            , m_materialName(name)
            , m_shader(shader)
            , m_textureId(textureId)
            , m_globalLighting(globalLighting)
            , m_specularPower(specularPower)
            , m_specularIntensity(specularIntensity)
            {
                
            }
            
            DiffuseSpecularMaterial::~DiffuseSpecularMaterial()
            {
                
            }
            
            const Eegeo::Rendering::TMaterialId DiffuseSpecularMaterial::GetId() const
            {
                return m_materialId;
            }
        
            const Eegeo::Rendering::Shader& DiffuseSpecularMaterial::GetShader() const
            {
                return m_shader;
            }
            
            void DiffuseSpecularMaterial::SetState(Eegeo::Rendering::GLState& glState) const
            {
                m_shader.Use(glState);
                
                glState.DepthFunc(GL_LEQUAL);
                glState.CullFace.Enable();
                glState.CullFaceMode(GL_BACK);
                
                glState.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glState.BlendEquation(GL_FUNC_ADD);
                glState.ColorMask(true, true, true, true);
                
                bool repeatTexture = true;
                Eegeo::Rendering::TextureMinifyType textureMinifyType = Eegeo::Rendering::TextureMinify_LinearMipmap_Linear;
                Eegeo::Helpers::GLHelpers::BindTexture2D(glState, m_shader.GetDiffuseSamplerId(), m_textureId, textureMinifyType, repeatTexture);
                
                m_shader.SetLightColors(m_globalLighting.GetColors());
                m_shader.SetLightDirections(m_globalLighting.GetLightDirectionMatrixForCameraPosition());
                
                Eegeo::dv3 lightDirection = m_globalLighting.GetLightDirectionMatrixForCameraPosition().GetRow(0);
                m_shader.SetLightDirection(lightDirection.ToSingle());
                
                m_shader.SetSpecularPower(m_specularPower);
                m_shader.SetSpecularIntensity(m_specularIntensity);
            }
            
            void DiffuseSpecularMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const
            {
                const Renderables::LitRenderable& renderable = *static_cast<const Renderables::LitRenderable*>(renderableBase);
                
                if(renderable.IsReflection())
                {
                    glState.StencilTest.Enable();
                    
                    glState.DepthMask(GL_FALSE);
                    
                    glState.FrontFace(GL_CCW);
                    
                    glState.StencilFunc(GL_EQUAL, 1, Eegeo::Rendering::StencilMapLayerMask::UserArea);
                    glState.StencilMask(0x00);
                }
                else
                {
                    glState.StencilTest.Disable();
                    
                    glState.DepthMask(GL_TRUE);
                    
                    glState.FrontFace(GL_CW);
                }
                
                m_shader.SetModelMatrix(renderable.GetWorldMatrix());
                m_shader.SetModelRotationMatrix(renderable.GetWorldRotationMatrix());
                m_shader.SetMVP(renderable.GetModelViewProjection());
                
                m_shader.SetInverseTransposeWorldMatrix(renderable.GetInverseTransposeModelMatrix());
                
                if (renderable.IsDepthTest())
                {
                    glState.DepthTest.Enable();
                }
                else
                {
                    glState.DepthTest.Disable();
                }
                
                if (renderable.IsAlphaBlend())
                {
                    glState.Blend.Enable();
                    glState.DepthMask(GL_FALSE);
                }
                else
                {
                    glState.Blend.Disable();
                    glState.DepthMask(GL_TRUE);
                }
            }
            
            const std::string& DiffuseSpecularMaterial::GetName() const
            {
                return m_materialName;
            }
        }
    }
}