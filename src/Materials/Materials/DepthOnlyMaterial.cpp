// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DepthOnlyMaterial.h"
#include "BlankShader.h"
#include "RenderableBase.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Materials
        {
            DepthOnlyMaterial::DepthOnlyMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                                 const std::string& name,
                                                 Shaders::BlankShader& shader)
            : m_id(materialId)
            , m_name(name)
            , m_shader(shader)
            {
            }
            
            const Eegeo::Rendering::TMaterialId DepthOnlyMaterial::GetId() const
            {
                return m_id;
            }
            
            const Eegeo::Rendering::Shader& DepthOnlyMaterial::GetShader() const
            {
                return m_shader;
            }
            
            const std::string& DepthOnlyMaterial::GetName() const
            {
                return m_name;
            }
            
            void DepthOnlyMaterial::SetState(Eegeo::Rendering::GLState& glState) const
            {
                m_shader.Use(glState);
                
                glState.BindTexture2D(0);
                glState.ColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
                
                glState.DepthMask(GL_TRUE);
                glState.DepthTest.Enable();
                
                glState.StencilTest.Disable();
                
                glState.CullFace.Enable();
                glState.FrontFace(GL_CW);
                glState.CullFaceMode(GL_BACK);
            }
            
            void DepthOnlyMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const
            {
                m_shader.SetMVP(renderableBase->GetModelViewProjection());
            }
        }
    }
}