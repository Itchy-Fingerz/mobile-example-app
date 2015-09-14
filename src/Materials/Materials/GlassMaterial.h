// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMaterial.h"
#include "Rendering.h"
#include "Lighting.h"
#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Shaders
        {
            class GlassShader;
        }
        
        namespace Materials
        {
            class GlassMaterial : public Eegeo::Rendering::Materials::IMaterial
            {
            public:
                GlassMaterial(const Eegeo::Rendering::TMaterialId materialId,
                              const std::string& name,
                              Shaders::GlassShader& shader,
                              Eegeo::Rendering::TTextureId reflectionTextureId,
                              Eegeo::Rendering::TTextureId cubeTextureId);
                
                const Eegeo::Rendering::TMaterialId GetId() const;
                
                const Eegeo::Rendering:: Shader& GetShader() const;
                
                void SetState(Eegeo::Rendering::GLState& glState) const;
                
                void SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const;
                
                const std::string& GetName() const;
                                
            private:
                Eegeo::Rendering::TMaterialId m_materialId;
                std::string m_materialName;
                Shaders::GlassShader& m_shader;
                Eegeo::Rendering::TTextureId m_reflectionTextureId;
                Eegeo::Rendering::TTextureId m_cubeTextureId;
            };
        }
    }
}