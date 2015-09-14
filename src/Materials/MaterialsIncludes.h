// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Materials
    {
        class IMaterialsModule;
        class IGeometryController;
        
        class MaterialRenderableFilter;
        class MaterialStore;
        class TextureStore;
        
        class ICubeTextureFileLoader;
        
        namespace Renderables
        {
            class MaterialRenderableBase;
            class BufferRenderable;
            class GlassRenderable;
            class LitRenderable;
            class ChromeRenderable;
        }
        
        namespace Materials
        {
            class DiffuseSpecularMaterial;
            class ChromeMaterial;
            class GlassMaterial;
            class StencilMaterial;
            class DepthOnlyMaterial;
        }
        
        namespace Shaders
        {
            class DiffuseSpecularShader;
            class ChromeShader;
            class GlassShader;
            class BlankShader;
        }
    }
}