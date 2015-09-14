// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Shader.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Shaders
        {
            class DiffuseSpecularShader : public Eegeo::Rendering::Shader
            {
            public:
                static DiffuseSpecularShader* Create(const Eegeo::Rendering::TShaderId shaderId);
                
                ~DiffuseSpecularShader();
                
                void Use(Eegeo::Rendering::GLState& glState) const;
                
                void SetMVP(const Eegeo::m44& mvp) const;
                
                void SetModelMatrix(const Eegeo::m44& modelMatrix) const;
                
                void SetModelRotationMatrix(const Eegeo::m44& modelRotationMatrix) const;
                
                void SetInverseTransposeWorldMatrix(const Eegeo::m44& inverseTransposeWorldMatrix) const;
                
                void SetLightColors(const Eegeo::m44& colors) const;
                
                void SetLightDirections(const Eegeo::m44& dirs) const;
                
                void SetLightDirection(const Eegeo::v3& dir) const;
                
                void SetSpecularPower(float specularPower) const;
                
                void SetSpecularIntensity(float specularIntensity) const;
                
                const GLuint GetDiffuseSamplerId() const;
                
            protected:
                DiffuseSpecularShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexShaderCode, const std::string& fragmentShaderCode);
                
            private:
                GLuint m_mvpUniformLocation;
                GLuint m_modelMatrixUniformLocation;
                GLuint m_modelRotationMatrixUniformLocation;
                GLuint m_inverseTransposeWorldUniformLocation;
                GLuint m_lightDirectionsUniformLocation;
                GLuint m_lightColorsUniformLocation;
                GLuint m_diffuseTextureSamplerUniformLocation;
                GLuint m_lightDirectionUniformLocation;
                GLuint m_specularPowerUniformLocation;
                GLuint m_specularIntensityUniformLocation;
            };
        }
    }
}