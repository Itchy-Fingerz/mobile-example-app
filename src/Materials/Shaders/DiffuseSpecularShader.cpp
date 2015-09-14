// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DiffuseSpecularShader.h"
#include "ShaderMacros.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Shaders
        {
            namespace DiffuseSpecularShaderCode
            {
                const std::string PositionName = "Position";
                const std::string NormalName = "Normal";
                const std::string UVName = "UV";
                const std::string DiffuseName = "Diffuse";
                const std::string CubeName = "Cube";
                const std::string ModelMatrix = "ModelMatrix";
                const std::string ModelRotationMatrix = "ModelRotationMatrix";
                const std::string ModelViewProjectionMatrixName = "ModelViewProjectionMatrix";
                const std::string WorldInverseTransposeMatrixName = "WorldInverseTransposeMatrix";
                const std::string LightDirectionMatrixName = "LightDirections";
                const std::string LightColorMatrixName = "LightColors";
                const std::string LightDirectionName = "LightDirection";
                const std::string SpecularPowerName = "SpecularPower";
                const std::string SpecularIntensityName = "SpecularIntensity";
                
                const std::string _vertexDecls =
                "attribute mediump vec3 "+PositionName+";\n"
                "attribute mediump vec3 "+NormalName+";\n"
                "attribute mediump vec2 "+UVName+";\n"
                "varying lowp vec4 ColorVarying;\n"
                "varying mediump vec2 DestinationUV;\n"
                "varying mediump vec3 PositionVarying;\n"
                "varying mediump vec3 NormalVarying;\n"
                "varying mediump vec3 LightDirectionVarying;\n"
                "uniform highp mat4 "+ModelMatrix+";\n"
                "uniform highp mat4 "+ModelRotationMatrix+";\n"
                "uniform highp mat4 "+ModelViewProjectionMatrixName+";\n"
                "uniform highp mat4 "+WorldInverseTransposeMatrixName+";\n"
                "uniform highp mat4 "+LightDirectionMatrixName+";\n"
                "uniform highp mat4 "+LightColorMatrixName+";\n"
                "uniform highp vec3 "+LightDirectionName+";\n";
                
                const std::string _fragmentDecls =
                "varying lowp vec4 ColorVarying;\n"
                "varying mediump vec2 DestinationUV;\n"
                "varying mediump vec3 PositionVarying;\n"
                "varying mediump vec3 NormalVarying;\n"
                "varying mediump vec3 LightDirectionVarying;\n"
                "uniform sampler2D "+DiffuseName+";\n"
                "uniform highp float "+SpecularPowerName+";\n"
                "uniform highp float "+SpecularIntensityName+";\n";
                
                const std::string _vertexCode =
                "void main(void) { \n"
                "DestinationUV = UV;\n"
                "vec4 myNormal = vec4 ("+NormalName+", 1.0) * "+WorldInverseTransposeMatrixName+";\n"
                "myNormal.w = 0.0;\n"
                "vec4 dots = -normalize(myNormal) * "+LightDirectionMatrixName+";\n"
                "dots = clamp (dots, 0.0, 1.0);\n"
                "dots.w = 1.0;\n"
                "ColorVarying.rgb = ("+LightColorMatrixName+" * dots).rgb;\n"
                "ColorVarying.a = 1.0;\n"
                "PositionVarying = (" + ModelMatrix + " * vec4(Position, 1.0)).xyz;\n"
                "NormalVarying = normalize((" + ModelRotationMatrix + " * vec4(Normal, 1.0)).xyz);\n"
                "LightDirectionVarying = normalize((" + ModelRotationMatrix + " * vec4(" + LightDirectionName + ", 1.0)).xyz);\n"
                "gl_Position = "+ModelViewProjectionMatrixName+" * vec4(Position.xyz, 1.0);\n"
                "}";
                
                const std::string _fragmentCode =
                "void main(void) { \n"
                "highp vec3 posToEye = normalize(-PositionVarying);\n"
                "highp vec3 lightReflection = normalize(reflect(normalize(LightDirectionVarying), NormalVarying));\n"
                "highp float specularFactor = max(0.0, dot(normalize(posToEye), normalize(lightReflection)));\n"
                "specularFactor = pow(specularFactor, SpecularPower) * SpecularIntensity;\n"
                "gl_FragColor.rgba = " TEXTURE2D(Diffuse, DestinationUV) " * ColorVarying + vec4(vec3(1.0, 1.0, 1.0) * specularFactor, 0.0);\n"
                "}";
            }
            
            DiffuseSpecularShader* DiffuseSpecularShader::Create(const Eegeo::Rendering::TShaderId shaderId)
            {
                return Eegeo_NEW(DiffuseSpecularShader)(shaderId,
                                                        DiffuseSpecularShaderCode::_vertexDecls + DiffuseSpecularShaderCode::_vertexCode,
                                                        DiffuseSpecularShaderCode::_fragmentDecls + DiffuseSpecularShaderCode::_fragmentCode);
            }
            
            DiffuseSpecularShader::~DiffuseSpecularShader()
            {
            
            }
            
            void DiffuseSpecularShader::Use(Eegeo::Rendering::GLState& glState) const
            {
                UseProgram(glState);
            }
            
            void DiffuseSpecularShader::SetMVP(const Eegeo::m44& mvp) const
            {
                SetUniformM44(mvp, m_mvpUniformLocation, false);
            }
            
            void DiffuseSpecularShader::SetModelMatrix(const Eegeo::m44& modelMatrix) const
            {
                SetUniformM44(modelMatrix, m_modelMatrixUniformLocation, false);
            }
            
            void DiffuseSpecularShader::SetModelRotationMatrix(const Eegeo::m44& modelRotationMatrix) const
            {
                SetUniformM44(modelRotationMatrix, m_modelRotationMatrixUniformLocation, false);
            }
            
            void DiffuseSpecularShader::SetInverseTransposeWorldMatrix(const Eegeo::m44& inverseTransposeWorldMatrix) const
            {
                SetUniformM44(inverseTransposeWorldMatrix, m_inverseTransposeWorldUniformLocation, false);
            }
            
            void DiffuseSpecularShader::SetLightColors(const Eegeo::m44& colors) const
            {
                SetUniformM44(colors, m_lightColorsUniformLocation, false);
            }
            
            void DiffuseSpecularShader::SetLightDirections(const Eegeo::m44& dirs) const
            {
                SetUniformM44(dirs, m_lightDirectionsUniformLocation, false);
            }
            
            void DiffuseSpecularShader::SetLightDirection(const Eegeo::v3& dir) const
            {
                SetUniformV3(dir, m_lightDirectionUniformLocation);
            }
            
            void DiffuseSpecularShader::SetSpecularPower(float specularPower) const
            {
                SetUniformFloat(specularPower, m_specularPowerUniformLocation);
            }
            
            void DiffuseSpecularShader::SetSpecularIntensity(float specularIntensity) const
            {
                SetUniformFloat(specularIntensity, m_specularIntensityUniformLocation);
            }
            
            const GLuint DiffuseSpecularShader::GetDiffuseSamplerId() const
            {
                return 0;
            }
            
            DiffuseSpecularShader::DiffuseSpecularShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
            : Eegeo::Rendering::Shader(shaderId)
            {
                CompileProgram(vertexShaderCode, fragmentShaderCode);
                
                m_modelMatrixUniformLocation = GetUniformLocation(DiffuseSpecularShaderCode::ModelMatrix);
                m_modelRotationMatrixUniformLocation = GetUniformLocation(DiffuseSpecularShaderCode::ModelRotationMatrix);
                m_mvpUniformLocation = GetUniformLocation(DiffuseSpecularShaderCode::ModelViewProjectionMatrixName);
                m_inverseTransposeWorldUniformLocation = GetUniformLocation(DiffuseSpecularShaderCode::WorldInverseTransposeMatrixName);
                m_lightDirectionsUniformLocation = GetUniformLocation(DiffuseSpecularShaderCode::LightDirectionMatrixName);
                m_lightColorsUniformLocation = GetUniformLocation(DiffuseSpecularShaderCode::LightColorMatrixName);
                m_diffuseTextureSamplerUniformLocation = GetUniformLocation(DiffuseSpecularShaderCode::DiffuseName);
                m_lightDirectionUniformLocation = GetUniformLocation(DiffuseSpecularShaderCode::LightDirectionName);
                m_specularPowerUniformLocation = GetUniformLocation(DiffuseSpecularShaderCode::SpecularPowerName);
                m_specularIntensityUniformLocation  = GetUniformLocation(DiffuseSpecularShaderCode::SpecularIntensityName);
            }
        }
    }
}