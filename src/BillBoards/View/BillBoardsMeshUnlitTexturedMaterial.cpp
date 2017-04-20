// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "BillBoardsMeshUnlitTexturedMaterial.h"
#include "TexturedUniformColoredShader.h"
#include "TextureMinifyType.h"
#include "GLHelpers.h"
#include "RenderableBase.h"
#include "BillBoardsMeshRenderable.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace View
        {
            BillBoardsMeshUnlitTexturedMaterial::BillBoardsMeshUnlitTexturedMaterial(
                                                                               const Eegeo::Rendering::TMaterialId materialId,
                                                                               const std::string& debugName,
                                                                               Eegeo::Rendering::Shaders::TexturedUniformColoredShader& shader,
                                                                               Eegeo::Rendering::TTextureId textureId,
                                                                               BillBoardService &billBoardService,
                                                                                     bool isVideo)
            : m_id(materialId)
            , m_debugName(debugName)
            , m_shader(shader)
            , m_textureId(textureId)
            , m_billBoardService(billBoardService)
            , m_isVideo(isVideo)
            , m_isAnimating(false)
            , m_currentAlpha(0.0)
            , m_isTapped(false)
            {
            }
            
            BillBoardsMeshUnlitTexturedMaterial::~BillBoardsMeshUnlitTexturedMaterial()
            {
                if(m_textureId)
                {
                    Eegeo_GL(glDeleteTextures(1, &m_textureId));
                    m_textureId = NULL;
                }
            }
            
            const Eegeo::Rendering::Shader& BillBoardsMeshUnlitTexturedMaterial::GetShader() const
            {
                return m_shader;
            }            
            
            void BillBoardsMeshUnlitTexturedMaterial::SetState(Eegeo::Rendering::GLState& glState) const
            {
                m_shader.Use(glState);
                
                glState.DepthFunc(GL_LEQUAL);
                glState.CullFace.Enable();
                glState.FrontFace(GL_CW);
                if(!m_isVideo)
                    glState.CullFaceMode(GL_BACK);
                else
                    glState.CullFaceMode(GL_FRONT);
                glState.StencilTest.Disable();                
                
                
                glState.Blend.Enable();
                glState.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glState.BlendEquation(GL_FUNC_ADD);
                glState.ColorMask(true, true, true, true);
                
                Eegeo_GL(glActiveTexture(GL_TEXTURE0));
                
                bool repeatTexture = false;
                Eegeo::Rendering::TextureMinifyType textureMinifyType = Eegeo::Rendering::TextureMinify_Linear;
                Eegeo::Helpers::GLHelpers::BindTexture2D(glState, m_shader.GetDiffuseSamplerId(), m_textureId, textureMinifyType, repeatTexture);
                
                
                if(m_isVideo && m_isAnimating)
                {
                    m_billBoardService.RenderVideoBillBoard();
                }
                
            }
            
            void BillBoardsMeshUnlitTexturedMaterial::SetAnimatingState(bool isAnimating) const
            {
                m_isAnimating = isAnimating;
            }
            
            void BillBoardsMeshUnlitTexturedMaterial::SetTappedState(bool isTapped) const
            {
                m_isTapped = isTapped;
            }
            
            bool BillBoardsMeshUnlitTexturedMaterial::GetAnimatingState() const
            {
                return m_isAnimating;
            }
            
            void BillBoardsMeshUnlitTexturedMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const
            {
                const BillBoardsMeshRenderable& exampleMeshRenderable = *static_cast<const BillBoardsMeshRenderable*>(renderableBase);
                m_shader.SetMVP(exampleMeshRenderable.GetModelViewProjection());
                
                if (exampleMeshRenderable.IsDepthTest())
                {
                    glState.DepthTest.Enable();
                }
                else
                {
                    glState.DepthTest.Disable();
                }
                
                if (exampleMeshRenderable.IsAlphaBlend())
                {
                    glState.Blend.Enable();
                    glState.DepthMask(GL_FALSE);
                }
                else
                {
                    glState.Blend.Disable();
                    glState.DepthMask(GL_TRUE);
                }
                
                Eegeo::v4 quadColor = exampleMeshRenderable.GetColor();
                
                if(m_currentAlpha < 0.5)
                {
                    m_currentAlpha = m_currentAlpha + 0.05;
                }
                if(m_isTapped && m_currentAlpha < 1.0)
                {
                    m_currentAlpha = m_currentAlpha + 0.05;
                }
                
                quadColor.SetW(m_currentAlpha);
                m_shader.SetColor(quadColor);
            }
            
            void BillBoardsMeshUnlitTexturedMaterial::SetTextureId(Eegeo::Rendering::TTextureId textureId) const
            {
                if(m_textureId)
                {
                    Eegeo_GL(glDeleteTextures(1, &m_textureId));
                    m_textureId = NULL;                    
                }
                m_textureId = textureId;
            }
        }
    }
}
