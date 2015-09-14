// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Modules.h"
#include "Lighting.h"
#include "Rendering.h"
#include "MaterialsIncludes.h"

namespace ExampleApp
{
    namespace Materials
    {
        class MaterialStore : protected Eegeo::NonCopyable
        {
        public:
            MaterialStore(const TextureStore& textureStore,
                          Eegeo::Modules::Core::RenderingModule& renderingModule,
                          const Eegeo::Lighting::GlobalLighting& globalLighting);
            
            ~MaterialStore();
            
            Eegeo::Rendering::Materials::IMaterial& GetStencilMaterial() const;
            Eegeo::Rendering::Materials::IMaterial& GetDepthOnlyMaterial() const;
            Eegeo::Rendering::Materials::IMaterial& GetDiffuseSpecularMaterial() const;
            Eegeo::Rendering::Materials::IMaterial& GetFloorDiffuseSpecularMaterial() const;
            Eegeo::Rendering::Materials::IMaterial& GetChromeMaterial() const;
            Eegeo::Rendering::Materials::IMaterial& GetGlassMaterial() const;
            
        private:
            Shaders::BlankShader* m_pBlankShader;
            Materials::StencilMaterial* m_pStencilMaterial;
            Materials::DepthOnlyMaterial* m_pDepthOnlyMaterial;
            
            Shaders::DiffuseSpecularShader* m_pDiffuseSpecularShader;
            Materials::DiffuseSpecularMaterial* m_pDiffuseSpecularMaterial;
            Materials::DiffuseSpecularMaterial* m_pFloorDiffuseSpecularMaterial;
            
            Shaders::ChromeShader* m_pChromeShader;
            Materials::ChromeMaterial* m_pChromeMaterial;
            
            Shaders::GlassShader* m_pGlassShader;
            Materials::GlassMaterial* m_pGlassMaterial;
        };
    }
}