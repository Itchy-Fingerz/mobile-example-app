// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IRenderableFilter.h"
#include "Types.h"
#include "MaterialsIncludes.h"
#include <vector>

namespace ExampleApp
{
    namespace Materials
    {
        class MaterialRenderableFilter : public Eegeo::Rendering::IRenderableFilter, private Eegeo::NonCopyable
        {
        public:
            MaterialRenderableFilter(Eegeo::Rendering::RenderableFilters& renderableFilters);
            
            ~MaterialRenderableFilter();
            
            void AddMaterialRenderable(Renderables::MaterialRenderableBase& renderable);
            void RemoveMaterialRenderable(Renderables::MaterialRenderableBase& renderable);
            
            void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
        private:
            typedef std::vector<Renderables::MaterialRenderableBase*> MaterialRenderableVector;
            
            MaterialRenderableVector m_renderables;
            
            Eegeo::Rendering::RenderableFilters& m_renderableFilters;
        };
    }
}