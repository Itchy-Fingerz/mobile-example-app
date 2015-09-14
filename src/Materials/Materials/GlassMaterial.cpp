// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GlassMaterial.h"
#include "GlassShader.h"
#include "GlobalLighting.h"
#include "TextureMinifyType.h"
#include "GLHelpers.h"
#include "GlassRenderable.h"
#include "StencilMapLayerMask.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Materials
        {
            GlassMaterial::GlassMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                         const std::string& name,
                                         Shaders::GlassShader& shader,
                                         Eegeo::Rendering::TTextureId reflectionTextureId,
                                         Eegeo::Rendering::TTextureId cubeTextureId)
            : m_materialId(materialId)
            , m_materialName(name)
            , m_shader(shader)
            , m_reflectionTextureId(reflectionTextureId)
            , m_cubeTextureId(cubeTextureId)
            {
                
            }
            
            const Eegeo::Rendering::TMaterialId GlassMaterial::GetId() const
            {
                return m_materialId;
            }
        
            const Eegeo::Rendering::Shader& GlassMaterial::GetShader() const
            {
                return m_shader;
            }
            
            void GlassMaterial::SetState(Eegeo::Rendering::GLState& glState) const
            {
                m_shader.Use(glState);
                
                glState.DepthFunc(GL_LEQUAL);
                glState.CullFace.Enable();
                glState.CullFaceMode(GL_BACK);
                glState.StencilTest.Disable();
                
                glState.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glState.BlendEquation(GL_FUNC_ADD);
                glState.ColorMask(true, true, true, true);
                
                glState.Blend.Enable();
                glState.DepthMask(GL_FALSE);
                
                bool repeatTexture = true;
                Eegeo::Rendering::TextureMinifyType textureMinifyType = Eegeo::Rendering::TextureMinify_LinearMipmap_Linear;
                Eegeo::Helpers::GLHelpers::BindTexture2D(glState, m_shader.GetReflectionSamplerId(), m_reflectionTextureId, textureMinifyType, repeatTexture);
                
                glState.ActiveTexture(GL_TEXTURE0 + m_shader.GetCubeSamplerId());
                
                Eegeo_GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
                Eegeo_GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
                Eegeo_GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
                
                glState.BindTextureCubeMap(m_cubeTextureId);
                
                glState.DepthTest.Enable();
            }
            
            void GlassMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const
            {
                const Renderables::GlassRenderable& renderable = *static_cast<const Renderables::GlassRenderable*>(renderableBase);
                
                m_shader.SetModelMatrix(renderable.GetWorldMatrix());
                m_shader.SetModelRotationMatrix(renderable.GetWorldRotationMatrix());
                m_shader.SetInverseModelRotationMatrix(renderable.GetInverseWorldRotationMatrix());
                m_shader.SetMVP(renderable.GetModelViewProjection());
                
                m_shader.SetEyePosition(renderable.GetEyePosition());
                
                if(renderable.IsReflection())
                {
                    glState.StencilTest.Enable();
                    
                    glState.FrontFace(GL_CCW);
                    
                    glState.StencilFunc(GL_EQUAL, 1, Eegeo::Rendering::StencilMapLayerMask::UserArea);
                    glState.StencilMask(0x00);
                }
                else
                {
                    glState.StencilTest.Disable();
                    
                    glState.FrontFace(GL_CW);
                }
            }
            
            const std::string& GlassMaterial::GetName() const
            {
                return m_materialName;
            }
        }
    }
}