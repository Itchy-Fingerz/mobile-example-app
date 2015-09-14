// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Shader.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Shaders
        {
            class GlassShader : public Eegeo::Rendering::Shader
            {
            public:
                static GlassShader* Create(const Eegeo::Rendering::TShaderId shaderId);
                
                ~GlassShader();
                
                void Use(Eegeo::Rendering::GLState& glState) const;
                
                void SetMVP(const Eegeo::m44& mvp) const;
                
                void SetModelMatrix(const Eegeo::m44& modelMatrix) const;
                
                void SetModelRotationMatrix(const Eegeo::m44& modelRotationMatrix) const;
                
                void SetInverseModelRotationMatrix(const Eegeo::m44& inverseModelRotationMatrix) const;
                
                void SetEyePosition(const Eegeo::v3& eyePosition) const;
                
                const GLuint GetReflectionSamplerId() const;
                
                const GLuint GetCubeSamplerId() const;
                
            protected:
                GlassShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
                
            private:
                GLuint m_mvpUniformLocation;
                GLuint m_modelMatrixUniformLocation;
                GLuint m_modelRotationMatrixUniformLocation;
                GLuint m_ReflectionTextureSamplerUniformLocation;
                GLuint m_cubeTextureSamplerUniformLocation;
                GLuint m_inverseModelRotationUniformLocation;
                GLuint m_eyePositionUniformLocation;
                
                const GLuint m_reflectionSamplerId;
                const GLuint m_cubeMapSamplerId;
            };
        }
    }
}