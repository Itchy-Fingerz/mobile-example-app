// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GlassShader.h"
#include "ShaderMacros.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Shaders
        {
            namespace GlassShaderCode
            {
                const std::string PositionName = "Position";
                const std::string NormalName = "Normal";
                const std::string UVName = "UV";
                const std::string ReflectionTextureName = "ReflectionTexture";
                const std::string CubeMapName = "CubeMap";
                const std::string ModelMatrix = "ModelMatrix";
                const std::string ModelRotationMatrix = "ModelRotationMatrix";
                const std::string ModelViewProjectionMatrixName = "ModelViewProjectionMatrix";
                const std::string InverseModelRotationMatrixName = "InverseModelRotationMatrix";
                const std::string EyePositionName = "EyePosition";
                
                const std::string _vertexDecls =
                "attribute mediump vec3 "+PositionName+";\n"
                "attribute mediump vec3 "+NormalName+";\n"
                "attribute mediump vec2 "+UVName+";\n"
                "varying mediump vec3 PositionVarying;\n"
                "varying mediump vec3 NormalVarying;\n"
                "varying mediump vec2 DestinationUV;\n"
                "uniform highp mat4 "+ModelMatrix+";\n"
                "uniform highp mat4 "+ModelRotationMatrix+";\n"
                "uniform highp mat4 "+ModelViewProjectionMatrixName+";\n";
                
                const std::string _fragmentDecls =
                "varying mediump vec3 PositionVarying;\n"
                "varying mediump vec3 NormalVarying;\n"
                "varying mediump vec2 DestinationUV;\n"
                "uniform sampler2D "+ReflectionTextureName+";\n"
                "uniform samplerCube "+CubeMapName+";\n"
                "uniform mediump mat4 "+InverseModelRotationMatrixName+";\n"
                "uniform mediump vec3 "+EyePositionName+";\n";
                
                const std::string _vertexCode =
                "void main(void) { \n"
                "DestinationUV = UV;\n"
                "NormalVarying = normalize((" + ModelRotationMatrix + " * vec4(Normal, 0.0)).xyz);\n"
                "PositionVarying = (" + ModelMatrix + " * vec4(Position, 1.0)).xyz;\n"
                "gl_Position = "+ModelViewProjectionMatrixName+" * vec4(Position.xyz, 1.0);\n"
                "}";
                
                const std::string _fragmentCode =
                "void main(void) { \n"
                "mediump vec3 eyeToPos = normalize(PositionVarying - " + EyePositionName + ");\n"
                "mediump vec3 eyeReflection = reflect(eyeToPos, NormalVarying);\n"
                "eyeReflection = (" + InverseModelRotationMatrixName + " * vec4(eyeReflection, 0.0)).xyz;\n"
                "highp vec4 reflectionColor = textureCube(" + CubeMapName + ", normalize(eyeReflection));\n"
                "lowp vec4 reflectionTexColor = " TEXTURE2D(ReflectionTexture, DestinationUV) ";\n"
                "reflectionTexColor.a = 0.2;\n"
                "gl_FragColor.rgba = reflectionTexColor + reflectionColor.rgba;\n"
                "}";
            }
            
            GlassShader* GlassShader::Create(const Eegeo::Rendering::TShaderId shaderId)
            {
                return Eegeo_NEW(GlassShader)(shaderId,
                                              GlassShaderCode::_vertexDecls + GlassShaderCode::_vertexCode,
                                              GlassShaderCode::_fragmentDecls + GlassShaderCode::_fragmentCode);
            }
            
            GlassShader::~GlassShader()
            {
                
            }
            
            void GlassShader::Use(Eegeo::Rendering::GLState& glState) const
            {
                UseProgram(glState);
            }
            
            void GlassShader::SetMVP(const Eegeo::m44& mvp) const
            {
                SetUniformM44(mvp, m_mvpUniformLocation, false);
            }
            
            void GlassShader::SetModelMatrix(const Eegeo::m44& modelMatrix) const
            {
                SetUniformM44(modelMatrix, m_modelMatrixUniformLocation, false);
            }
            
            void GlassShader::SetModelRotationMatrix(const Eegeo::m44& modelRotationMatrix) const
            {
                SetUniformM44(modelRotationMatrix, m_modelRotationMatrixUniformLocation, false);
            }
            
            void GlassShader::SetInverseModelRotationMatrix(const Eegeo::m44& inverseModelRotationMatrix) const
            {
                SetUniformM44(inverseModelRotationMatrix, m_inverseModelRotationUniformLocation, false);
            }
            
            void GlassShader::SetEyePosition(const Eegeo::v3& eyePosition) const
            {
                SetUniformV3(eyePosition, m_eyePositionUniformLocation);
            }
            
            const GLuint GlassShader::GetReflectionSamplerId() const
            {
                return m_reflectionSamplerId;
            }
            
            const GLuint GlassShader::GetCubeSamplerId() const
            {
                return m_cubeMapSamplerId;
            }
            
            GlassShader::GlassShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexShaderCode, const std::string& fragmentShaderCode)
            : Eegeo::Rendering::Shader(shaderId)
            , m_reflectionSamplerId(0)
            , m_cubeMapSamplerId(1)
            {
                CompileProgram(vertexShaderCode, fragmentShaderCode);
                
                m_modelMatrixUniformLocation = GetUniformLocation(GlassShaderCode::ModelMatrix);
                m_modelRotationMatrixUniformLocation = GetUniformLocation(GlassShaderCode::ModelRotationMatrix);
                m_mvpUniformLocation = GetUniformLocation(GlassShaderCode::ModelViewProjectionMatrixName);
                m_ReflectionTextureSamplerUniformLocation = GetUniformLocation(GlassShaderCode::ReflectionTextureName);
                m_cubeTextureSamplerUniformLocation = GetUniformLocation(GlassShaderCode::CubeMapName);
                m_inverseModelRotationUniformLocation = GetUniformLocation(GlassShaderCode::InverseModelRotationMatrixName);
                m_eyePositionUniformLocation = GetUniformLocation(GlassShaderCode::EyePositionName);
                
                Eegeo_GL(glUniform1i(m_ReflectionTextureSamplerUniformLocation, m_reflectionSamplerId));
                Eegeo_GL(glUniform1i(m_cubeTextureSamplerUniformLocation, m_cubeMapSamplerId));
            }
        }
    }
}