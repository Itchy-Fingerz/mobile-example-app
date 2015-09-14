// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "StencilMaterial.h"
#include "BlankShader.h"
#include "RenderableBase.h"
#include "StencilMapLayerMask.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Materials
        {
            StencilMaterial::StencilMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                             const std::string& name,
                                             Shaders::BlankShader& shader)
            : m_id(materialId)
            , m_name(name)
            , m_shader(shader)
            {
            }
            
            const Eegeo::Rendering::TMaterialId StencilMaterial::GetId() const
            {
                return m_id;
            }
            
            const Eegeo::Rendering::Shader& StencilMaterial::GetShader() const
            {
                return m_shader;
            }
            
            const std::string& StencilMaterial::GetName() const
            {
                return m_name;
            }
            
            void StencilMaterial::SetState(Eegeo::Rendering::GLState& glState) const
            {
                m_shader.Use(glState);
                
                glState.StencilMask(Eegeo::Rendering::StencilMapLayerMask::UserArea);
                glClearStencil(0);
                glClear(GL_STENCIL_BUFFER_BIT);
                
                glState.BindTexture2D(0);
                glState.ColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
                
                glState.DepthMask(GL_FALSE);
                glState.DepthTest.Enable();
                glState.DepthFunc(GL_LESS);
                
                glState.StencilTest.Enable();
                
                glState.CullFace.Enable();
                glState.FrontFace(GL_CW);
                
                glState.StencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
                
                glState.StencilFunc(GL_ALWAYS, 1, Eegeo::Rendering::StencilMapLayerMask::UserArea);
            }
            
            void StencilMaterial::SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const
            {
                m_shader.SetMVP(renderableBase->GetModelViewProjection());
            }
        }
    }
}