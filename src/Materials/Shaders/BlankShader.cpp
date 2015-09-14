// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BlankShader.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Shaders
        {
            namespace BlankShaderCode
            {
                const std::string PositionName = "Position";
                const std::string ModelViewProjectionMatrixName = "ModelViewProjectionMatrix";
                
                const std::string _vertexDecls =
                "attribute mediump vec4 " + PositionName + ";\n"
                "uniform highp mat4 " + ModelViewProjectionMatrixName + ";\n";
                
                const std::string _vertexCode =
                "void main(void) { \n"
                "gl_Position = " + ModelViewProjectionMatrixName + " * vec4(" + PositionName + ".xyz, 1.0);\n"
                "}";
                
                const std::string _fragmentCode =
                "void main(void) { \n"
                "gl_FragColor.rgba = vec4(0.0, 0.0, 0.0, 1.0); \n"
                "}";
            }
            
            BlankShader* BlankShader::Create(const Eegeo::Rendering::TShaderId shaderId)
            {
                return Eegeo_NEW(BlankShader)(shaderId,
                                              BlankShaderCode::_vertexDecls + BlankShaderCode::_vertexCode,
                                              BlankShaderCode::_fragmentCode);
            }
            
            void BlankShader::SetMVP(const Eegeo::m44& mvp) const
            {
                SetUniformM44(mvp, m_mvpUniformLocation, false);
            }
            
            void BlankShader::Use(Eegeo::Rendering::GLState& glState) const
            {
                UseProgram(glState);
            }
            
            BlankShader::BlankShader(const Eegeo::Rendering::TShaderId shaderId,
                                     const std::string& vertexShaderCode,
                                     const std::string& fragmentShaderCode) : Shader(shaderId)
            {
                CompileProgram(vertexShaderCode, fragmentShaderCode);
                m_mvpUniformLocation = GetUniformLocation(BlankShaderCode::ModelViewProjectionMatrixName);
            }
        }
    }
}