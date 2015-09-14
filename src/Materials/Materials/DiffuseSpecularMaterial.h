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
            class DiffuseSpecularShader;
        }
        
        namespace Materials
        {
            class DiffuseSpecularMaterial : public Eegeo::Rendering::Materials::IMaterial
            {
            public:
                DiffuseSpecularMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                        const std::string& name,
                                        Shaders::DiffuseSpecularShader& shader,
                                        Eegeo::Rendering::TTextureId textureId,
                                        float specularPower,
                                        float specularIntensity,
                                        const Eegeo::Lighting::GlobalLighting& globalLighting);
                
                ~DiffuseSpecularMaterial();
                
                const Eegeo::Rendering::TMaterialId GetId() const;
                
                const Eegeo::Rendering:: Shader& GetShader() const;
                
                void SetState(Eegeo::Rendering::GLState& glState) const;
                
                void SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const;
                
                const std::string& GetName() const;
                                
            private:
                Eegeo::Rendering::TMaterialId m_materialId;
                std::string m_materialName;
                Shaders::DiffuseSpecularShader& m_shader;
                Eegeo::Rendering::TTextureId m_textureId;
                float m_specularPower;
                float m_specularIntensity;
                const Eegeo::Lighting::GlobalLighting& m_globalLighting;
            };
        }
    }
}