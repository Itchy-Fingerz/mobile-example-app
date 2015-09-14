// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ChromeShader.h"
#include "ShaderMacros.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Shaders
        {
            namespace ChromeShaderCode
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
                const std::string LightPositionOffsetName = "LightPositionOffset";
                const std::string SpecularPowerName = "SpecularPower";
                const std::string SpecularIntensityName = "SpecularIntensity";
                const std::string SpecularStretchTangentName = "SpecularStretchTangent";
                
                const std::string _vertexDecls =
                "attribute highp vec3 "+PositionName+";\n"
                "attribute highp vec3 "+NormalName+";\n"
                "attribute mediump vec2 "+UVName+";\n"
                "varying lowp vec4 ColorVarying;\n"
                "varying mediump vec2 DestinationUV;\n"
                "varying highp vec3 PositionVarying;\n"
                "varying highp vec3 NormalVarying;\n"
                "varying highp vec3 LightPositionVarying;\n"
                "uniform highp mat4 "+ModelMatrix+";\n"
                "uniform highp mat4 "+ModelRotationMatrix+";\n"
                "uniform highp mat4 "+ModelViewProjectionMatrixName+";\n"
                "uniform highp mat4 "+WorldInverseTransposeMatrixName+";\n"
                "uniform highp mat4 "+LightDirectionMatrixName+";\n"
                "uniform highp mat4 "+LightColorMatrixName+";\n"
                "uniform highp vec3 "+LightPositionOffsetName+";\n";
                
                const std::string _fragmentDecls =
                "varying lowp vec4 ColorVarying;\n"
                "varying mediump vec2 DestinationUV;\n"
                "varying highp vec3 PositionVarying;\n"
                "varying highp vec3 NormalVarying;\n"
                "varying highp vec3 LightPositionVarying;\n"
                "uniform sampler2D "+DiffuseName+";\n"
                "uniform highp float "+SpecularPowerName+";\n"
                "uniform highp float "+SpecularIntensityName+";\n"
                "uniform mediump vec3 "+SpecularStretchTangentName+";\n";
                
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
                "LightPositionVarying = " + ModelMatrix + "[3].xyz + " + LightPositionOffsetName + ";\n"
                "gl_Position = "+ModelViewProjectionMatrixName+" * vec4(Position.xyz, 1.0);\n"
                "}";
                
                const std::string _fragmentCode =
                "void main(void) { \n"
                "highp vec3 posToEye = normalize(-PositionVarying);\n"
                "highp vec3 lightDirection = normalize(PositionVarying - LightPositionVarying);\n"
                "highp vec3 lightReflection = normalize(reflect(lightDirection, NormalVarying));\n"
                "lightReflection = mix(normalize(lightReflection), normalize(posToEye), abs("+SpecularStretchTangentName+"));\n"
                "highp float specularFactor = max(0.0, dot(normalize(posToEye), normalize(lightReflection)));\n"
                "specularFactor = pow(specularFactor, SpecularPower) * SpecularIntensity;\n"
                "lowp vec4 texColor = " TEXTURE2D(Diffuse, DestinationUV) ";\n"
                "highp float texLuminance = length(texColor.r + texColor.g + texColor.b) / 3.0;\n"
                "gl_FragColor.rgba = texColor * ColorVarying + vec4(vec3(1.0, 1.0, 1.0) * specularFactor * texLuminance, 0.0);\n"
                "}";
            }
            
            ChromeShader* ChromeShader::Create(const Eegeo::Rendering::TShaderId shaderId)
            {
                return Eegeo_NEW(ChromeShader)(shaderId,
                                               ChromeShaderCode::_vertexDecls + ChromeShaderCode::_vertexCode,
                                               ChromeShaderCode::_fragmentDecls + ChromeShaderCode::_fragmentCode);
            }
            
            ChromeShader::~ChromeShader()
            {
                
            }
            
            void ChromeShader::Use(Eegeo::Rendering::GLState& glState) const
            {
                UseProgram(glState);
            }
            
            void ChromeShader::SetMVP(const Eegeo::m44& mvp) const
            {
                SetUniformM44(mvp, m_mvpUniformLocation, false);
            }
            
            void ChromeShader::SetModelMatrix(const Eegeo::m44& modelMatrix) const
            {
                SetUniformM44(modelMatrix, m_modelMatrixUniformLocation, false);
            }
            
            void ChromeShader::SetModelRotationMatrix(const Eegeo::m44& modelRotationMatrix) const
            {
                SetUniformM44(modelRotationMatrix, m_modelRotationMatrixUniformLocation, false);
            }
            
            void ChromeShader::SetInverseTransposeWorldMatrix(const Eegeo::m44& inverseTransposeWorldMatrix) const
            {
                SetUniformM44(inverseTransposeWorldMatrix, m_inverseTransposeWorldUniformLocation, false);
            }
            
            void ChromeShader::SetLightColors(const Eegeo::m44& colors) const
            {
                SetUniformM44(colors, m_lightColorsUniformLocation, false);
            }
            
            void ChromeShader::SetLightDirections(const Eegeo::m44& dirs) const
            {
                SetUniformM44(dirs, m_lightDirectionsUniformLocation, false);
            }
            
            void ChromeShader::SetLightPositionOffset(const Eegeo::v3& positionOffset) const
            {
                SetUniformV3(positionOffset, m_lightPositionOffsetUniformLocation);
            }
            
            void ChromeShader::SetSpecularPower(float specularPower) const
            {
                SetUniformFloat(specularPower, m_specularPowerUniformLocation);
            }
            
            void ChromeShader::SetSpecularIntensity(float specularIntensity) const
            {
                SetUniformFloat(specularIntensity, m_specularIntensityUniformLocation);
            }
            
            void ChromeShader::SetSpecularStretchTangent(const Eegeo::v3& specularStretchTangent) const
            {
                SetUniformV3(specularStretchTangent, m_specularStretchTangentUniformLocation);
            }
            
            const GLuint ChromeShader::GetDiffuseSamplerId() const
            {
                return 0;
            }
            
            ChromeShader::ChromeShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
            : Eegeo::Rendering::Shader(shaderId)
            {
                CompileProgram(vertexShaderCode, fragmentShaderCode);
                
                m_modelMatrixUniformLocation = GetUniformLocation(ChromeShaderCode::ModelMatrix);
                m_modelRotationMatrixUniformLocation = GetUniformLocation(ChromeShaderCode::ModelRotationMatrix);
                m_mvpUniformLocation = GetUniformLocation(ChromeShaderCode::ModelViewProjectionMatrixName);
                m_inverseTransposeWorldUniformLocation = GetUniformLocation(ChromeShaderCode::WorldInverseTransposeMatrixName);
                m_lightDirectionsUniformLocation = GetUniformLocation(ChromeShaderCode::LightDirectionMatrixName);
                m_lightColorsUniformLocation = GetUniformLocation(ChromeShaderCode::LightColorMatrixName);
                m_diffuseTextureSamplerUniformLocation = GetUniformLocation(ChromeShaderCode::DiffuseName);
                m_lightPositionOffsetUniformLocation = GetUniformLocation(ChromeShaderCode::LightPositionOffsetName);
                m_specularPowerUniformLocation = GetUniformLocation(ChromeShaderCode::SpecularPowerName);
                m_specularIntensityUniformLocation = GetUniformLocation(ChromeShaderCode::SpecularIntensityName);
                m_specularStretchTangentUniformLocation = GetUniformLocation(ChromeShaderCode::SpecularStretchTangentName);
            }
        }
    }
}