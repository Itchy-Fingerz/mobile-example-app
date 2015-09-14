// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMaterial.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace Shaders
        {
            class BlankShader;
        }
        
        namespace Materials
        {
            class StencilMaterial : public Eegeo::Rendering::Materials::IMaterial, protected Eegeo::NonCopyable
            {
            public:
                StencilMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                const std::string& name,
                                Shaders::BlankShader& shader);
                
                const Eegeo::Rendering::TMaterialId GetId() const;
                const Eegeo::Rendering::Shader& GetShader() const;
                const std::string& GetName() const;
                
                void SetState(Eegeo::Rendering::GLState& glState) const;
                
                void SetStatePerRenderable(const Eegeo::Rendering::RenderableBase* renderableBase, Eegeo::Rendering::GLState& glState) const;
            protected:
                const Eegeo::Rendering::TMaterialId m_id;
                const std::string m_name;
                Shaders::BlankShader& m_shader;
            };
        }
    }
}