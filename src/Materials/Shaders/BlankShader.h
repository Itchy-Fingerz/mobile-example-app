// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Shader.h"
#include "IdTypes.h"
#include "VectorMathDecl.h"
#include <string>

namespace ExampleApp
{
    namespace Materials
    {
        namespace Shaders
        {
            class BlankShader : public Eegeo::Rendering::Shader
            {
            public:
                static BlankShader* Create(const Eegeo::Rendering::TShaderId shaderId);
                
                void SetMVP(const Eegeo::m44& mvp) const;
                
                void Use(Eegeo::Rendering::GLState& glState) const;
                
            protected:
                BlankShader(const Eegeo::Rendering::TShaderId shaderId,
                            const std::string& vertexShaderCode,
                            const std::string& fragmentShaderCode);
                
            private:
                GLuint m_mvpUniformLocation;
            };
        }
    }
}
