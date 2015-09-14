// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Shader.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Shaders
        {
            class ChromeShader : public Eegeo::Rendering::Shader
            {
            public:
                static ChromeShader* Create(const Eegeo::Rendering::TShaderId shaderId);
                
                ~ChromeShader();
                
                void Use(Eegeo::Rendering::GLState& glState) const;
                
                void SetMVP(const Eegeo::m44& mvp) const;
                
                void SetModelMatrix(const Eegeo::m44& modelMatrix) const;
                
                void SetModelRotationMatrix(const Eegeo::m44& modelRotationMatrix) const;
                
                void SetInverseTransposeWorldMatrix(const Eegeo::m44& inverseTransposeWorldMatrix) const;
                
                void SetLightColors(const Eegeo::m44& colors) const;
                
                void SetLightDirections(const Eegeo::m44& dirs) const;
                
                void SetLightPositionOffset(const Eegeo::v3& positionOffset) const;
                
                void SetSpecularPower(float specularPower) const;
                
                void SetSpecularIntensity(float specularIntensity) const;
                
                void SetSpecularStretchTangent(const Eegeo::v3& specularStretchTangent) const;
                
                const GLuint GetDiffuseSamplerId() const;
                
            protected:
                ChromeShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
                
            private:
                GLuint m_mvpUniformLocation;
                GLuint m_modelMatrixUniformLocation;
                GLuint m_modelRotationMatrixUniformLocation;
                GLuint m_inverseTransposeWorldUniformLocation;
                GLuint m_lightDirectionsUniformLocation;
                GLuint m_lightColorsUniformLocation;
                GLuint m_diffuseTextureSamplerUniformLocation;
                GLuint m_lightPositionOffsetUniformLocation;
                GLuint m_specularPowerUniformLocation;
                GLuint m_specularIntensityUniformLocation;
                GLuint m_specularStretchTangentUniformLocation;
            };
        }
    }
}