// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "RenderableHelpers.h"

#include "VectorMath.h"
#include "VertexBindingPool.h"
#include "Mesh.h"
#include "IMaterial.h"
#include "Shader.h"

#include "LitRenderable.h"
#include "GlassRenderable.h"
#include "BufferRenderable.h"
#include "ChromeRenderable.h"

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
                                                            Eegeo::Rendering::LayerIds::Values renderLayer)
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = vertexBindingPool.GetVertexBinding(mesh.GetVertexLayout(), material.GetShader().GetVertexAttributes());
                
                Renderables::LitRenderable* pRenderable = new Renderables::LitRenderable(renderLayer,
                                                                                         ecefPosition,
                                                                                         material,
                                                                                         vertexBinding,
                                                                                         mesh,
                                                                                         depthTest,
                                                                                         alphaBlend,
                                                                                         isReflection);
                
                return pRenderable;
            }
            
            Renderables::GlassRenderable* CreateGlassRenderable(Eegeo::Rendering::Mesh& mesh,
                                                                Eegeo::Rendering::Materials::IMaterial& material,
                                                                Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                                                const Eegeo::dv3 ecefPosition,
                                                                bool depthTest,
                                                                bool isReflection,
                                                                Eegeo::Rendering::LayerIds::Values renderLayer)
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = vertexBindingPool.GetVertexBinding(mesh.GetVertexLayout(), material.GetShader().GetVertexAttributes());
                
                Renderables::GlassRenderable* pRenderable = new Renderables::GlassRenderable(renderLayer,
                                                                                             ecefPosition,
                                                                                             material,
                                                                                             vertexBinding,
                                                                                             mesh,
                                                                                             depthTest,
                                                                                             isReflection);
                
                return pRenderable;
            }
            
            Renderables::BufferRenderable* CreateBufferRenderable(Eegeo::Rendering::Mesh& mesh,
                                                                  Eegeo::Rendering::Materials::IMaterial& material,
                                                                  Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                                                  const Eegeo::dv3 ecefPosition,
                                                                  Eegeo::Rendering::LayerIds::Values renderLayer)
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = vertexBindingPool.GetVertexBinding(mesh.GetVertexLayout(), material.GetShader().GetVertexAttributes());
                
                Renderables::BufferRenderable* pRenderable = new Renderables::BufferRenderable(renderLayer,
                                                                                               ecefPosition,
                                                                                               material,
                                                                                               vertexBinding,
                                                                                               mesh);
                
                return pRenderable;
            }
            
            Renderables::ChromeRenderable* CreateChromeRenderable(Eegeo::Rendering::Mesh& mesh,
                                                                  Eegeo::Rendering::Materials::IMaterial& material,
                                                                  Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                                                  const Eegeo::dv3 ecefPosition,
                                                                  bool depthTest,
                                                                  bool alphaBlend,
                                                                  bool isReflection,
                                                                  Eegeo::Rendering::LayerIds::Values renderLayer,
                                                                  const Eegeo::v3& lightPositionOffset)
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = vertexBindingPool.GetVertexBinding(mesh.GetVertexLayout(), material.GetShader().GetVertexAttributes());
                
                Renderables::ChromeRenderable* pRenderable = new Renderables::ChromeRenderable(renderLayer,
                                                                                               ecefPosition,
                                                                                               material,
                                                                                               vertexBinding,
                                                                                               mesh,
                                                                                               depthTest,
                                                                                               alphaBlend,
                                                                                               isReflection,
                                                                                               lightPositionOffset);
                
                return pRenderable;
            }
        }
    }
}