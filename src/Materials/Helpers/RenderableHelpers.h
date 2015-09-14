// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VectorMathDecl.h"
#include "MaterialsIncludes.h"
#include "Rendering.h"
#include "LayerIds.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace RenderableHelpers
        {
            Renderables::LitRenderable* CreateLitRenderable(Eegeo::Rendering::Mesh& mesh,
                                                            Eegeo::Rendering::Materials::IMaterial& material,
                                                            Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                                            const Eegeo::dv3 ecefPosition,
                                                            bool depthTest,
                                                            bool alphaBlend,
                                                            bool isReflection,
                                                            Eegeo::Rendering::LayerIds::Values renderLayer);
            
            Renderables::GlassRenderable* CreateGlassRenderable(Eegeo::Rendering::Mesh& mesh,
                                                                Eegeo::Rendering::Materials::IMaterial& material,
                                                                Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                                                const Eegeo::dv3 ecefPosition,
                                                                bool depthTest,
                                                                bool isReflection,
                                                                Eegeo::Rendering::LayerIds::Values renderLayer);
            
            Renderables::BufferRenderable* CreateBufferRenderable(Eegeo::Rendering::Mesh& mesh,
                                                                  Eegeo::Rendering::Materials::IMaterial& material,
                                                                  Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                                                  const Eegeo::dv3 ecefPosition,
                                                                  Eegeo::Rendering::LayerIds::Values renderLayer);
            
            Renderables::ChromeRenderable* CreateChromeRenderable(Eegeo::Rendering::Mesh& mesh,
                                                                  Eegeo::Rendering::Materials::IMaterial& material,
                                                                  Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                                                  const Eegeo::dv3 ecefPosition,
                                                                  bool depthTest,
                                                                  bool alphaBlend,
                                                                  bool isReflection,
                                                                  Eegeo::Rendering::LayerIds::Values renderLayer,
                                                                  const Eegeo::v3& lightPositionOffset);
        }
    }
}