// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MaterialsModule.h"

#include "RenderingModule.h"

#include "GeometryController.h"
#include "MaterialRenderableFilter.h"
#include "MaterialStore.h"
#include "TextureStore.h"

namespace ExampleApp
{
    namespace Materials
    {
        MaterialsModule::MaterialsModule(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                         Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                                         const Eegeo::Space::LatLongAltitude& originLatLongAltitude,
                                         const Eegeo::Lighting::GlobalLighting& globalLighting,
                                         Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                                         ICubeTextureFileLoader& cubeTextureFileLoader)
        : m_pRenderableFilter(NULL)
        , m_pTextureStore(NULL)
        , m_pMaterialStore(NULL)
        , m_pGeometryController(NULL)
        {
            m_pRenderableFilter = Eegeo_NEW(MaterialRenderableFilter)(renderingModule.GetRenderableFilters());
            
            m_pTextureStore = Eegeo_NEW(TextureStore)(cubeTextureFileLoader,
                                                      textureFileLoader);
            
            m_pMaterialStore = Eegeo_NEW(MaterialStore)(*m_pTextureStore,
                                                        renderingModule,
                                                        globalLighting);
            
            m_pGeometryController = Eegeo_NEW(GeometryController)(*m_pMaterialStore,
                                                                  *m_pRenderableFilter,
                                                                  renderingModule,
                                                                  originLatLongAltitude,
                                                                  debugRenderer);
        }
        
        MaterialsModule::~MaterialsModule()
        {
            Eegeo_DELETE m_pGeometryController;
            m_pGeometryController = NULL;
            
            Eegeo_DELETE m_pMaterialStore;
            m_pMaterialStore = NULL;
            
            Eegeo_DELETE m_pTextureStore;
            m_pTextureStore = NULL;
            
            Eegeo_DELETE m_pRenderableFilter;
            m_pRenderableFilter = NULL;
        }
        
        IGeometryController& MaterialsModule::GetGeometryController() const
        {
            return *m_pGeometryController;
        }
    }
}
