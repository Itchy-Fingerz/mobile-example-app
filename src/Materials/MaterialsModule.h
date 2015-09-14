// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMaterialsModule.h"
#include "Types.h"
#include "Modules.h"
#include "Helpers.h"
#include "Lighting.h"
#include "DebugRendering.h"
#include "MaterialsIncludes.h"
#include "Space.h"

namespace ExampleApp
{
    namespace Materials
    {   
        class MaterialsModule : public IMaterialsModule, private Eegeo::NonCopyable
        {
        public:
            MaterialsModule(Eegeo::Modules::Core::RenderingModule& renderingModule,
                            Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                            const Eegeo::Space::LatLongAltitude& originLatLongAltitude,
                            const Eegeo::Lighting::GlobalLighting& globalLighting,
                            Eegeo::DebugRendering::DebugRenderer& debugRenderer,
                            ICubeTextureFileLoader& cubeTextureFileLoader);
            
            ~MaterialsModule();
            
            IGeometryController& GetGeometryController() const;
            
        private:
            MaterialRenderableFilter* m_pRenderableFilter;
            TextureStore* m_pTextureStore;
            MaterialStore* m_pMaterialStore;
            IGeometryController* m_pGeometryController;
        };
    }
}
