// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IRenderableFilter.h"
#include "MeshExampleConfig.h"
#include "RenderTexture.h"
#include "Rendering.h"
#include "Modules.h"
#include "Helpers.h"
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"

#include "VectorMath.h"
#include <vector>
#include "AppInterface.h"
#include "InteriorInteractionModel.h"
#include "IAppCameraController.h"
#include "AggregateCollisionBvhProvider.h"
namespace ExampleApp
{
    
    namespace BillBoards
    {
        namespace View
        {
            class BillBoardsMeshRenderable;
            class BillBoardsMeshUnlitTexturedMaterial;
            
            
            class MeshExample : public Eegeo::Rendering::IRenderableFilter
            {
            public:
                typedef std::vector<BillBoardsMeshRenderable*> BillBoardsMeshRenderableVector;
                
                MeshExample(Eegeo::Modules::Core::RenderingModule& renderingModule,
                            Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                            Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                            Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                            const MeshExampleConfig& config,
                            //Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                            AppCamera::SdkModel::IAppCameraController& iCameraController);
                
                virtual ~MeshExample();
                
                static std::string GetName()
                {
                    return "MeshExample";
                }
                
                std::string Name() const
                {
                    return GetName();
                }
                
                void Start();
                void Update(float dt);
                
                void Draw() {}
                void Suspend() {}
                
                // IRenderableFilter interface
                void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
                void updateImage();
                void OnSingleTap(const AppInterface::TapData& data,Eegeo::Collision::AggregateCollisionBvhProvider&collisionBvhProvider);
                
            private:
                
                Eegeo::Modules::Core::RenderingModule& m_renderingModule;
                Eegeo::Helpers::ITextureFileLoader& m_textureFileLoader;
                Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;
                MeshExampleConfig m_config;
                
                Eegeo::Helpers::GLHelpers::TextureInfo m_textureInfo;
                
                Eegeo::Rendering::VertexLayouts::VertexLayout* m_pPositionUvVertexLayout;
                Eegeo::Rendering::Shaders::TexturedUniformColoredShader* m_pShader;
                BillBoardsMeshUnlitTexturedMaterial* m_pMaterial;
                Eegeo::Rendering::Mesh* m_pUnlitBoxMesh;
                BillBoardsMeshRenderableVector m_renderables;
                
                Eegeo::m33 m_basisToEcef;
                
                float m_timer;
                bool flag;
                //Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                AppCamera::SdkModel::IAppCameraController& m_iCameraController;


                bool PerformRayPick(const Eegeo::dv3 &rayOrigin,
                               Eegeo::dv3 &rayDirection,
                               Eegeo::dv3 &out_rayIntersectionPoint,
                               double &out_intersectionParam,
                               float &out_terrainHeight,
                               float &out_heightAboveTerrain);

            };
        }
    }
}
