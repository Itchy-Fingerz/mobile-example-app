// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "QuadLineMeshUnlitColorMaterial.h"
#include "GLHelpers.h"
#include "RenderableBase.h"
#include "QuadLineRenderable.h"

namespace ExampleApp
{
    namespace PointingQuadRadialLine
    {
        
        void QuadLineMeshUnlitColorMaterial::SetState(Eegeo::Rendering::GLState& glState) const
        {
            m_shader.Use(glState);
            glState.Blend.Enable();
            glState.DepthFunc(GL_LEQUAL);
            glState.CullFace.Disable();
            glState.FrontFace(GL_CW);
            glState.CullFaceMode(GL_BACK);
            glState.StencilTest.Disable();
            
            glState.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glState.BlendEquation(GL_FUNC_ADD);
            
        }
    }
}