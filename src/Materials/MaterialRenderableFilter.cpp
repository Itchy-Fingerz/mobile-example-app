// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MaterialRenderableFilter.h"
#include "RenderableFilters.h"
#include "RenderContext.h"
#include "RenderCamera.h"
#include "RenderQueue.h"
#include "MaterialRenderableBase.h"
#include <algorithm>

namespace ExampleApp
{
    namespace Materials
    {
        MaterialRenderableFilter::MaterialRenderableFilter(Eegeo::Rendering::RenderableFilters& renderableFilters)
        : m_renderableFilters(renderableFilters)
        {
            m_renderableFilters.AddRenderableFilter(*this);
        }
        
        MaterialRenderableFilter::~MaterialRenderableFilter()
        {
            m_renderables.clear();
            m_renderableFilters.RemoveRenderableFilter(*this);
        }
        
        void MaterialRenderableFilter::AddMaterialRenderable(Renderables::MaterialRenderableBase& renderable)
        {
            m_renderables.push_back(&renderable);
        }
        
        void MaterialRenderableFilter::RemoveMaterialRenderable(Renderables::MaterialRenderableBase& renderable)
        {
            MaterialRenderableVector::iterator it = std::find(m_renderables.begin(), m_renderables.end(), &renderable);
            
            if(it != m_renderables.end())
            {
                m_renderables.erase(it);
            }
            else
            {
                Eegeo_TTY("Renderable not found to remove from MaterialRenderableFilter");
            }
        }
        
        void MaterialRenderableFilter::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
        {
            const Eegeo::Camera::RenderCamera& renderCamera = renderContext.GetRenderCamera();
            
            Eegeo::m44 viewProjection = renderCamera.GetViewProjectionMatrix();
            Eegeo::dv3 ecefCameraPosition = renderCamera.GetEcefLocation();
            
            for (MaterialRenderableVector::const_iterator it = m_renderables.begin(); it != m_renderables.end(); ++it)
            {
                Renderables::MaterialRenderableBase& renderable = *(*it);
                
                renderable.UpdateMatrices(ecefCameraPosition, viewProjection);
                
                renderQueue.EnqueueRenderable(renderable);
            }
        }
    }
}