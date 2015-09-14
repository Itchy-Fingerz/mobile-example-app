// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MaterialStore.h"

#include "RenderingModule.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "TextureStore.h"

#include "BlankShader.h"
#include "ChromeShader.h"
#include "GlassShader.h"
#include "DiffuseSpecularShader.h"

#include "StencilMaterial.h"
#include "DiffuseSpecularMaterial.h"
#include "ChromeMaterial.h"
#include "GlassMaterial.h"
#include "DepthOnlyMaterial.h"

namespace ExampleApp
{
    namespace Materials
    {
        MaterialStore::MaterialStore(const TextureStore& textureStore,
                      Eegeo::Modules::Core::RenderingModule& renderingModule,
                      const Eegeo::Lighting::GlobalLighting& globalLighting)
        {
            m_pBlankShader = Shaders::BlankShader::Create(renderingModule.GetShaderIdGenerator().GetNextId());
            
            m_pDiffuseSpecularShader = Shaders::DiffuseSpecularShader::Create(renderingModule.GetShaderIdGenerator().GetNextId());
            
            m_pChromeShader = Shaders::ChromeShader::Create(renderingModule.GetShaderIdGenerator().GetNextId());
            
            m_pGlassShader = Shaders::GlassShader::Create(renderingModule.GetShaderIdGenerator().GetNextId());
            
            m_pStencilMaterial = Eegeo_NEW(Materials::StencilMaterial)(renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                       "StencilMaterial",
                                                                       *m_pBlankShader);
            
            m_pDiffuseSpecularMaterial = Eegeo_NEW(Materials::DiffuseSpecularMaterial)(renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                                       "DiffuseSpecularMaterial",
                                                                                       *m_pDiffuseSpecularShader,
                                                                                       textureStore.GetChromeTextureID(),
                                                                                       10.0f,
                                                                                       0.2f,
                                                                                       globalLighting);
            
            m_pChromeMaterial = Eegeo_NEW(Materials::ChromeMaterial)(renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                     "ChromeMaterial",
                                                                     *m_pChromeShader,
                                                                     textureStore.GetChromeTextureID(),
                                                                     100.0f,
                                                                     0.65f,
                                                                     globalLighting);
            
            m_pGlassMaterial = Eegeo_NEW(Materials::GlassMaterial)(renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                   "GlassMaterial",
                                                                   *m_pGlassShader,
                                                                   textureStore.GetGlassTextureID(),
                                                                   textureStore.GetLightCubeTextureID());
            
            m_pFloorDiffuseSpecularMaterial = Eegeo_NEW(Materials::DiffuseSpecularMaterial)(renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                                            "FloorDiffuseSpecularMaterial",
                                                                                            *m_pDiffuseSpecularShader,
                                                                                            textureStore.GetFloorTextureID(),
                                                                                            10.0f,
                                                                                            0.1f,
                                                                                            globalLighting);
            
            m_pDepthOnlyMaterial = Eegeo_NEW(Materials::DepthOnlyMaterial)(renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                           "DepthOnlyMaterial",
                                                                           *m_pBlankShader);
        }
        
        MaterialStore::~MaterialStore()
        {
            Eegeo_DELETE m_pDepthOnlyMaterial;
            m_pDepthOnlyMaterial = NULL;
            
            Eegeo_DELETE m_pFloorDiffuseSpecularMaterial;
            m_pFloorDiffuseSpecularMaterial = NULL;
            
            Eegeo_DELETE m_pGlassMaterial;
            m_pGlassMaterial = NULL;
            
            Eegeo_DELETE m_pChromeMaterial;
            m_pChromeMaterial = NULL;
            
            Eegeo_DELETE m_pDiffuseSpecularMaterial;
            m_pDiffuseSpecularMaterial = NULL;
            
            Eegeo_DELETE m_pStencilMaterial;
            m_pStencilMaterial = NULL;
            
            Eegeo_DELETE m_pGlassShader;
            m_pGlassShader = NULL;
            
            Eegeo_DELETE m_pChromeShader;
            m_pChromeShader = NULL;
            
            Eegeo_DELETE m_pDiffuseSpecularShader;
            m_pDiffuseSpecularShader = NULL;
            
            Eegeo_DELETE m_pBlankShader;
            m_pBlankShader = NULL;
        }
        
        Eegeo::Rendering::Materials::IMaterial& MaterialStore::GetStencilMaterial() const
        {
            return *m_pStencilMaterial;
        }
        
        Eegeo::Rendering::Materials::IMaterial& MaterialStore::GetDepthOnlyMaterial() const
        {
            return *m_pDepthOnlyMaterial;
        }
        
        Eegeo::Rendering::Materials::IMaterial& MaterialStore::GetDiffuseSpecularMaterial() const
        {
            return *m_pDiffuseSpecularMaterial;
        }
        
        Eegeo::Rendering::Materials::IMaterial& MaterialStore::GetFloorDiffuseSpecularMaterial() const
        {
            return *m_pFloorDiffuseSpecularMaterial;
        }
        
        Eegeo::Rendering::Materials::IMaterial& MaterialStore::GetChromeMaterial() const
        {
            return *m_pChromeMaterial;
        }
        
        Eegeo::Rendering::Materials::IMaterial& MaterialStore::GetGlassMaterial() const
        {
            return *m_pGlassMaterial;
        }
    }
}
