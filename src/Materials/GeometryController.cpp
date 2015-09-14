// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GeometryController.h"
#include "MaterialsGeometryHelpers.h"
#include "EcefTangentBasis.h"
#include "CameraHelpers.h"
#include "MaterialRenderableFilter.h"
#include "Mesh.h"
#include "VertexLayout.h"
#include "RenderableHelpers.h"
#include "RenderingModule.h"
#include "MaterialStore.h"
#include "Bounds.h"
#include "DebugRenderer.h"

#include "MaterialRenderableBase.h"
#include "LitRenderable.h"
#include "GlassRenderable.h"
#include "BufferRenderable.h"
#include "ChromeRenderable.h"


namespace ExampleApp
{
    namespace Materials
    {
        GeometryController::GeometryController(MaterialStore& materialStore,
                                               MaterialRenderableFilter& renderableFilter,
                                               Eegeo::Modules::Core::RenderingModule& renderingModule,
                                               const Eegeo::Space::LatLongAltitude& originLatLongAltitude,
                                               Eegeo::DebugRendering::DebugRenderer& debugRenderer)
        : m_showDebugAxes(true)
        , m_materialStore(materialStore)
        , m_renderableFilter(renderableFilter)
        , m_renderingModule(renderingModule)
        , m_pPositionNormalUvVertexLayout(NULL)
        , m_currentRotation(0.0f)
        , m_originLatLongAltitude(originLatLongAltitude)
        , m_centrePosition(originLatLongAltitude.ToECEF())
        , m_basisToEcef(Eegeo::m33::CreateIdentity())
        , m_debugRenderer(debugRenderer)
        {
            m_pPositionNormalUvVertexLayout = GeometryHelpers::CreatePositionNormalUvVertexLayout();
            
            Eegeo::Space::EcefTangentBasis basisFrame;
            Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(Eegeo::Space::LatLong::FromDegrees(m_originLatLongAltitude.GetLatitudeInDegrees(), m_originLatLongAltitude.GetLongitudeInDegrees()).ToECEF(),
                                                                              0.0,
                                                                              basisFrame);
            
            basisFrame.GetBasisOrientationAsMatrix(m_basisToEcef);
            
            CreateReflectiveFloor();
            CreateChromeObjects();
            CreateGlassPlanes();
            CreateAdditionalGeometry();
            
            for(MaterialRenderableVector::const_iterator it = m_renderables.begin(); it != m_renderables.end(); ++it)
            {
                (*it)->SetOrientationEcef(m_basisToEcef);
                m_renderableFilter.AddMaterialRenderable(*(*it));
            }
        }
        
        GeometryController::~GeometryController()
        {
            m_rotatingRenderables.clear();
            
            for(MaterialRenderableVector::iterator it = m_renderables.begin(); it != m_renderables.end(); ++it)
            {
                m_renderableFilter.RemoveMaterialRenderable(*(*it));
                delete (*it);
            }
            m_renderables.clear();
            
            for(MeshVector::const_iterator it = m_meshes.begin(); it != m_meshes.end(); ++it)
            {
                delete (*it);
            }
            m_meshes.clear();
            
            Eegeo_DELETE m_pPositionNormalUvVertexLayout;
        }
        
        void GeometryController::Update(float dt)
        {
            if(m_showDebugAxes)
            {
                const float axesSize = 1500.0f;
                
                m_debugRenderer.DrawAxes(m_centrePosition, m_basisToEcef.GetRow(0) * axesSize, m_basisToEcef.GetRow(1) * axesSize, m_basisToEcef.GetRow(2) * axesSize);
            }
            
            const float rotationSpeed = 1.0f;
            
            m_currentRotation += rotationSpeed * dt;
            
            Eegeo::m33 localOrientation;;
            localOrientation.Rotate((float)M_PI_4 / 2.0, m_currentRotation, (float)M_PI_4 / 2.0);
            
            for(MaterialRenderableVector::const_iterator it = m_rotatingRenderables.begin(); it != m_rotatingRenderables.end(); ++it)
            {
                (*it)->SetRotationMatrix(localOrientation);
            }
        }
        
        void GeometryController::CreateReflectiveFloor()
        {
            Eegeo::m33 planeBasis;
            planeBasis.Identity();
            planeBasis.RotateX((float)M_PI_2);
            
            Eegeo::Rendering::Mesh* planeMesh = GeometryHelpers::CreateLitPlaneMesh(Eegeo::v2(2000.0f, 2000.0f), 100.0f, planeBasis, *m_pPositionNormalUvVertexLayout, m_renderingModule.GetGlBufferPool());
            m_meshes.push_back(planeMesh);
            
            Renderables::BufferRenderable* pFloorStencilRenderable = RenderableHelpers::CreateBufferRenderable(*planeMesh,
                                                                                                               m_materialStore.GetStencilMaterial(),
                                                                                                               m_renderingModule.GetVertexBindingPool(),
                                                                                                               Eegeo::dv3::Mul(Eegeo::dv3(0.0f, 0.0f, 0.0f), m_basisToEcef) + m_centrePosition,
                                                                                                               Eegeo::Rendering::LayerIds::BeforeAll);
            m_renderables.push_back(pFloorStencilRenderable);
            
            Renderables::BufferRenderable* pFloorDepthRenderable = RenderableHelpers::CreateBufferRenderable(*planeMesh,
                                                                                                             m_materialStore.GetDepthOnlyMaterial(),
                                                                                                             m_renderingModule.GetVertexBindingPool(),
                                                                                                             Eegeo::dv3::Mul(Eegeo::dv3(0.0f, 0.0f, 0.0f), m_basisToEcef) + m_centrePosition,
                                                                                                             Eegeo::Rendering::LayerIds::BeforeWorld);
            m_renderables.push_back(pFloorDepthRenderable);
            
            Renderables::LitRenderable* pFloorRenderable = RenderableHelpers::CreateLitRenderable(*planeMesh,
                                                                                                  m_materialStore.GetFloorDiffuseSpecularMaterial(),
                                                                                                  m_renderingModule.GetVertexBindingPool(),
                                                                                                  Eegeo::dv3::Mul(Eegeo::dv3(0.0f, 0.0f, 0.0f), m_basisToEcef) + m_centrePosition,
                                                                                                  true,
                                                                                                  true,
                                                                                                  false,
                                                                                                  Eegeo::Rendering::LayerIds::AfterWorldTranslucency);
            m_renderables.push_back(pFloorRenderable);
        }
        
        void GeometryController::CreateGlassPlanes()
        {
            const Eegeo::v2 glassPlaneDimensions(1000.0f, 200.0f);
            
            std::vector<Eegeo::m33> glassPlaneBases;
            glassPlaneBases.resize(4);
            glassPlaneBases[0].RotateY(0.0f);
            glassPlaneBases[1].RotateY((float)M_PI_2);
            glassPlaneBases[2].RotateY((float)M_PI);
            glassPlaneBases[3].RotateY(-(float)M_PI_2);
            
            std::vector<Eegeo::dv3> glassPlanePositions;
            glassPlanePositions.resize(8);
            glassPlanePositions[0] = Eegeo::dv3(0.0, 100.0, -500.0);
            glassPlanePositions[1] = Eegeo::dv3(-500.0, 100.0, 0.0);
            glassPlanePositions[2] = Eegeo::dv3(0.0, 100.0, 500.0);
            glassPlanePositions[3] = Eegeo::dv3(500.0, 100.0, 0.0);
            glassPlanePositions[4] = Eegeo::dv3(0.0, 100.0, 500.0);
            glassPlanePositions[5] = Eegeo::dv3(500.0, 100.0, 0.0);
            glassPlanePositions[6] = Eegeo::dv3(0.0, 100.0, -500.0);
            glassPlanePositions[7] = Eegeo::dv3(-500.0, 100.0, 0.0);
            
            for(int i = 0; i < glassPlanePositions.size(); ++i)
            {
                Eegeo::Rendering::Mesh* glassPlaneMesh = GeometryHelpers::CreateLitPlaneMesh(glassPlaneDimensions,
                                                                                             Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2(5.0f, 1.0f)),
                                                                                             glassPlaneBases[i % 4],
                                                                                             *m_pPositionNormalUvVertexLayout,
                                                                                             m_renderingModule.GetGlBufferPool());
                m_meshes.push_back(glassPlaneMesh);
                
                Renderables::GlassRenderable* pGlassPlaneRenderable = RenderableHelpers::CreateGlassRenderable(*glassPlaneMesh,
                                                                                                               m_materialStore.GetGlassMaterial(),
                                                                                                               m_renderingModule.GetVertexBindingPool(),
                                                                                                               Eegeo::dv3::Mul(glassPlanePositions[i], m_basisToEcef) + m_centrePosition,
                                                                                                               true,
                                                                                                               false,
                                                                                                               Eegeo::Rendering::LayerIds::AfterAll);
                m_renderables.push_back(pGlassPlaneRenderable);
                
                Renderables::GlassRenderable* pGlassPlaneReflectionRenderable = RenderableHelpers::CreateGlassRenderable(*glassPlaneMesh,
                                                                                                                         m_materialStore.GetGlassMaterial(),
                                                                                                                         m_renderingModule.GetVertexBindingPool(),
                                                                                                                         Eegeo::dv3::Mul(glassPlanePositions[i], m_basisToEcef) + m_centrePosition,
                                                                                                                         true,
                                                                                                                         true,
                                                                                                                         Eegeo::Rendering::LayerIds::BeforeAll);
                pGlassPlaneReflectionRenderable->SetReflectionPlane(m_centrePosition, m_basisToEcef.GetRow(1));
                m_renderables.push_back(pGlassPlaneReflectionRenderable);
            }
        }
        
        void GeometryController::CreateChromeObjects()
        {
            const Eegeo::v3 columnDimensions(75.0f, 300.0f, 75.0f);
            
            std::vector<Eegeo::dv3> columnPositions;
            columnPositions.push_back(Eegeo::dv3(250.0, 150.0f, 250.0));
            columnPositions.push_back(Eegeo::dv3(-250.0, 150.0f, 250.0));
            columnPositions.push_back(Eegeo::dv3(-250.0, 150.0f, -250.0));
            columnPositions.push_back(Eegeo::dv3(250.0, 150.0f, -250.0));
            
            const Eegeo::dv3 lightPosition(0.0f, 100.0f, 0.0f);
            
            std::vector<Eegeo::dv3> columnLightOffsets;
            for(int i = 0; i < columnPositions.size(); ++i)
            {
                columnLightOffsets.push_back(lightPosition - columnPositions[i]);
            }
            
            Eegeo::Rendering::Mesh* pColumnMesh = GeometryHelpers::CreateLitBoxMesh(columnDimensions, *m_pPositionNormalUvVertexLayout, m_renderingModule.GetGlBufferPool());
            m_meshes.push_back(pColumnMesh);
            
            for(int i = 0; i < columnPositions.size(); ++i)
            {
                Renderables::ChromeRenderable* pColumnRenderable = RenderableHelpers::CreateChromeRenderable(*pColumnMesh,
                                                                                                             m_materialStore.GetChromeMaterial(),
                                                                                                             m_renderingModule.GetVertexBindingPool(),
                                                                                                             Eegeo::dv3::Mul(columnPositions[i], m_basisToEcef) + m_centrePosition,
                                                                                                             true,
                                                                                                             false,
                                                                                                             false,
                                                                                                             Eegeo::Rendering::LayerIds::AfterWorld,
                                                                                                             columnLightOffsets[i].ToSingle());
                m_renderables.push_back(pColumnRenderable);
                
                Renderables::ChromeRenderable* pColumnReflectionRenderable = RenderableHelpers::CreateChromeRenderable(*pColumnMesh,
                                                                                                                       m_materialStore.GetChromeMaterial(),
                                                                                                                       m_renderingModule.GetVertexBindingPool(),
                                                                                                                       Eegeo::dv3::Mul(columnPositions[i], m_basisToEcef) + m_centrePosition,
                                                                                                                       true,
                                                                                                                       false,
                                                                                                                       true,
                                                                                                                       Eegeo::Rendering::LayerIds::BeforeAll,
                                                                                                                       columnLightOffsets[i].ToSingle());
                pColumnReflectionRenderable->SetReflectionPlane(m_centrePosition, m_basisToEcef.GetRow(1));
                m_renderables.push_back(pColumnReflectionRenderable);
            }
            
            const Eegeo::v3 boxDimensions(75.0f, 75.0f, 75.0f);
            
            std::vector<Eegeo::dv3> boxPositions;
            boxPositions.push_back(Eegeo::dv3(625.0, 100.0f, 625.0));
            boxPositions.push_back(Eegeo::dv3(-625.0, 100.0f, 625.0));
            boxPositions.push_back(Eegeo::dv3(-625.0, 100.0f, -625.0));
            boxPositions.push_back(Eegeo::dv3(625.0, 100.0f, -625.0));
            
            std::vector<Eegeo::dv3> boxLightOffsets;
            for(int i = 0; i < boxPositions.size(); ++i)
            {
                boxLightOffsets.push_back(lightPosition - boxPositions[i]);
            }
            
            Eegeo::Rendering::Mesh* pBoxMesh = GeometryHelpers::CreateLitBoxMesh(boxDimensions, *m_pPositionNormalUvVertexLayout, m_renderingModule.GetGlBufferPool());
            m_meshes.push_back(pBoxMesh);
            
            for(int i = 0; i < boxPositions.size(); ++i)
            {
                Renderables::ChromeRenderable* pBoxRenderable = RenderableHelpers::CreateChromeRenderable(*pBoxMesh,
                                                                                                          m_materialStore.GetChromeMaterial(),
                                                                                                          m_renderingModule.GetVertexBindingPool(),
                                                                                                          Eegeo::dv3::Mul(boxPositions[i], m_basisToEcef) + m_centrePosition,
                                                                                                          true,
                                                                                                          false,
                                                                                                          false,
                                                                                                          Eegeo::Rendering::LayerIds::AfterWorld,
                                                                                                          boxLightOffsets[i].ToSingle());
                m_renderables.push_back(pBoxRenderable);
                
                Renderables::ChromeRenderable* pBoxReflectionRenderable = RenderableHelpers::CreateChromeRenderable(*pBoxMesh,
                                                                                                                    m_materialStore.GetChromeMaterial(),
                                                                                                                    m_renderingModule.GetVertexBindingPool(),
                                                                                                                    Eegeo::dv3::Mul(boxPositions[i], m_basisToEcef) + m_centrePosition,
                                                                                                                    true,
                                                                                                                    false,
                                                                                                                    true,
                                                                                                                    Eegeo::Rendering::LayerIds::BeforeAll,
                                                                                                                    boxLightOffsets[i].ToSingle());
                pBoxReflectionRenderable->SetReflectionPlane(m_centrePosition, m_basisToEcef.GetRow(1));
                m_renderables.push_back(pBoxReflectionRenderable);
                
                m_rotatingRenderables.push_back(pBoxRenderable);
                m_rotatingRenderables.push_back(pBoxReflectionRenderable);
            }
        }
        
        void GeometryController::CreateAdditionalGeometry()
        {
            Eegeo::Rendering::Mesh* boxMesh = GeometryHelpers::CreateLitBoxMesh(Eegeo::v3(75.0f, 75.0f, 75.0f), *m_pPositionNormalUvVertexLayout, m_renderingModule.GetGlBufferPool());
            m_meshes.push_back(boxMesh);
            
            Renderables::LitRenderable* pBoxRenderable = RenderableHelpers::CreateLitRenderable(*boxMesh,
                                                                                                m_materialStore.GetDiffuseSpecularMaterial(),
                                                                                                m_renderingModule.GetVertexBindingPool(),
                                                                                                Eegeo::dv3::Mul(Eegeo::dv3(0.0f, 37.5f, 0.0f), m_basisToEcef) + m_centrePosition,
                                                                                                true,
                                                                                                false,
                                                                                                false,
                                                                                                Eegeo::Rendering::LayerIds::AfterWorld);
            m_renderables.push_back(pBoxRenderable);
            
            Renderables::LitRenderable* pBoxReflectionRenderable = RenderableHelpers::CreateLitRenderable(*boxMesh,
                                                                                                          m_materialStore.GetDiffuseSpecularMaterial(),
                                                                                                          m_renderingModule.GetVertexBindingPool(),
                                                                                                          Eegeo::dv3::Mul(Eegeo::dv3(0.0f, 37.5f, 0.0f), m_basisToEcef) + m_centrePosition,
                                                                                                          true,
                                                                                                          false,
                                                                                                          true,
                                                                                                          Eegeo::Rendering::LayerIds::BeforeAll);
            pBoxReflectionRenderable->SetReflectionPlane(m_centrePosition, m_basisToEcef.GetRow(1));
            m_renderables.push_back(pBoxReflectionRenderable);
        }
    }
}