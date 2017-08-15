// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "QuadLine.h"
#include "QuadLineRenderable.h"
#include "ColorMaterial.h"
#include "TriangleGeometryHelpers.h"

#include "RenderingModule.h"
#include "EcefTangentBasis.h"
#include "VertexLayoutPool.h"
#include "VertexLayout.h"
#include "VertexLayoutElement.h"
#include "Mesh.h"
#include "LayerIds.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "Colors.h"

#include "VertexBindingPool.h"
#include "LatLongAltitude.h"
#include "CoordinateConversion.h"
#include "RenderQueue.h"
#include "RenderableFilters.h"
#include "EnvironmentFlatteningService.h"
#include "CameraHelpers.h"
#include "RenderContext.h"
#include "RenderCamera.h"
#include "QuadLineMeshUnlitColorMaterial.h"

#include <algorithm>
#include <cmath>

namespace ExampleApp
{
    namespace PointingQuadRadialLine
    {
        namespace
        {
            struct PositionUvVertex
            {
                float x;
                float y;
                float z;
                float u;
                float v;
            };
            
            inline PositionUvVertex MakePositionUvVertex(const Eegeo::v3& pos, const Eegeo::v2& uv)
            {
                PositionUvVertex v;
                v.x = pos.x;
                v.y = pos.y;
                v.z = pos.z;
                v.u = uv.x;
                v.v = uv.y;
                return v;
            }
            
            inline PositionUvVertex GeometryHelpersVertexToPositionUvVertex(const TriangleGeometryHelpers::Vertex& v)
            {
                return MakePositionUvVertex(v.position, v.uv);
            }
            
            Eegeo::Rendering::VertexLayouts::VertexLayout* CreatePositionUvVertexLayout()
            {
                using namespace Eegeo::Rendering::VertexLayouts;
                VertexLayout* pLayout = new (VertexLayout)(sizeof(PositionUvVertex));
                
                int positionOffset = offsetof(PositionUvVertex, x);
                pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::Position, 3, GL_FLOAT,  positionOffset));
                
                int uvOffset = offsetof(PositionUvVertex, u);
                pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::UV, 2, GL_FLOAT, uvOffset));
                
                return pLayout;
            }
            
            Eegeo::Rendering::Mesh* CreateUnlitBoxMesh(float width, float height, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool)
            {
                Eegeo::v3 halfDimensions(width/2, height, width/2);
                std::vector<TriangleGeometryHelpers::Vertex> boxVertices;
                std::vector<u16> triangleIndices;
                
                BuildBox(halfDimensions, boxVertices, triangleIndices);
                
                std::vector<PositionUvVertex> unlitVertices;
                
                std::transform(boxVertices.begin(), boxVertices.end(), std::back_inserter(unlitVertices), GeometryHelpersVertexToPositionUvVertex);
                
                size_t vertexBufferSizeBytes = sizeof(PositionUvVertex) * unlitVertices.size();
                size_t indexBufferSizeBytes = sizeof(u16) * triangleIndices.size();
                
                return new (Eegeo::Rendering::Mesh)(
                                                    vertexLayout,
                                                    glBufferPool,
                                                    unlitVertices.data(),
                                                    vertexBufferSizeBytes,
                                                    triangleIndices.data(),
                                                    indexBufferSizeBytes,
                                                    static_cast<u32>(triangleIndices.size()),
                                                    "UnlitBoxMesh"
                                                    );
            }
            
            QuadLineRenderable* CreateExampleMeshRenderable(Eegeo::Rendering::Mesh& mesh, Eegeo::Rendering::Materials::IMaterial& material, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool, const Eegeo::dv3 ecefPosition)
            {
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding =
                vertexBindingPool.GetVertexBinding(mesh.GetVertexLayout(), material.GetShader().GetVertexAttributes());
                
                const Eegeo::Rendering::LayerIds::Values renderLayer = Eegeo::Rendering::LayerIds::AfterWorld;
                const bool depthTest = true;
                const bool alphaBlend = true;
                const bool translateWithEnvironmentFlattening = false;
                const bool scaleWithEnvironmentFlattening = false;
                
                QuadLineRenderable* pUnlitBoxRenderable = new QuadLineRenderable(renderLayer,
                                                                                       ecefPosition,
                                                                                       material,
                                                                                       vertexBinding,
                                                                                       mesh,
                                                                                       Eegeo::Rendering::Colors::WHITE,
                                                                                       depthTest,
                                                                                       alphaBlend,
                                                                                       translateWithEnvironmentFlattening,
                                                                                       scaleWithEnvironmentFlattening);
                
                return pUnlitBoxRenderable;
            }
            
        }        
        
        QuadLine::QuadLine(Eegeo::Modules::Core::RenderingModule& renderingModule,
                                 Eegeo::DebugRendering::DebugRenderer &debugRenderer,
                                 Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                 Eegeo::v4 quadColor,
                                 Eegeo::dv3 fromEcef,
                                 Eegeo::dv3 toEcef,
                                 float tileLength,
                                 float thickness,
                                 Eegeo::Rendering::TShaderId shaderId)
        : m_renderingModule(renderingModule)
        , m_debugRenderer(debugRenderer)
        , m_environmentFlatteningService(environmentFlatteningService)
        , m_quadColor(quadColor)
        , m_pPositionUvVertexLayout(NULL)
        , m_pShader(NULL)
        , m_pMaterial(NULL)
        , m_pUnlitBoxMesh(NULL)
        , m_fromEcef(fromEcef)
        , m_toEcef(toEcef)
        , m_tileLength(tileLength)
        , m_thickness(thickness)
        , m_currentStep(0)
        
        {
            m_pPositionUvVertexLayout = CreatePositionUvVertexLayout();
            
            Eegeo::Rendering::RenderableFilters& platformRenderableFilters = m_renderingModule.GetRenderableFilters();
            
            m_pShader = Eegeo::Rendering::Shaders::ColorShader::Create(shaderId);
            
            m_pMaterial = new (QuadLineMeshUnlitColorMaterial)(
                                                               m_renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                               "QuadLineMat",
                                                               *m_pShader,
                                                               m_quadColor
                                                               );
            
            Start();
            
            platformRenderableFilters.AddRenderableFilter(*this);
            m_debugRenderer.SetLineWidth(10.0f);
            
        }
        
        QuadLine::~QuadLine()
        {
            Eegeo::Rendering::RenderableFilters& platformRenderableFilters = m_renderingModule.GetRenderableFilters();
            
            platformRenderableFilters.RemoveRenderableFilter(*this);
            
            delete m_pPositionUvVertexLayout;
            delete m_pMaterial;
            delete m_pShader;
            delete m_pUnlitBoxMesh;
            delete m_pRenderable;
        }
        
        void QuadLine::Start()
        {
            
            m_pUnlitBoxMesh = CreateUnlitBoxMesh(m_thickness*4, m_thickness, *m_pPositionUvVertexLayout, m_renderingModule.GetGlBufferPool());
            
            Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool = m_renderingModule.GetVertexBindingPool();
            
            m_pRenderable = CreateExampleMeshRenderable(*m_pUnlitBoxMesh, *m_pMaterial, vertexBindingPool, m_toEcef);
        }
        
        void QuadLine::Update(float dt)
        {
            
        }
        
        void QuadLine::DrawQuadLine()
        {
            
            Eegeo::dv3 centerPoint = m_toEcef + (m_fromEcef-m_toEcef)/2.0f;
            
            double radius = Eegeo::Math::Sqrtd(
                                               Eegeo::Math::Pow(m_toEcef.GetX()-centerPoint.GetX(), 2) +
                                               Eegeo::Math::Pow(m_toEcef.GetY()-centerPoint.GetY(), 2) +
                                               Eegeo::Math::Pow(m_toEcef.GetZ()-centerPoint.GetZ(), 2));
            
            float angle = 0.0f;
            double angleIter = Eegeo::Math::Rad2Deg(Eegeo::Math::ATan2(m_tileLength+0.3, radius));
            int i=0;
            m_currentStep += 5;
            
            double iter = 180.f/angleIter;
            Eegeo::dv3 delta = (m_toEcef-m_fromEcef)/iter;
            
            Eegeo::m33 tangentBasis = GetLookAtOrientationMatrix(m_fromEcef.ToSingle(), m_toEcef.ToSingle(), m_fromEcef.ToSingle().Norm());
            
            Eegeo::m33 lastOrientation;
            for (Eegeo::dv3 ecefCenter=m_fromEcef; angle<170 ; ecefCenter+=delta)
            {
                
                if(angle < m_currentStep)
                    m_quadColor.SetW((float)(i/iter) * 1);
                else
                {
                    m_quadColor.SetW((float)(i/iter) * 0);
                    break;
                }
                
                Eegeo::dv3 pos = centerPoint +
                (tangentBasis.GetRow(2) * radius * Eegeo::Math::Cos(Eegeo::Math::Deg2Rad(angle))) +
                (tangentBasis.GetRow(1) * radius * Eegeo::Math::Sin(Eegeo::Math::Deg2Rad(angle)));
                
                //Calculating orientation with larger radius
                Eegeo::dv3 posOrientation = centerPoint +
                (tangentBasis.GetRow(2) * 50 * Eegeo::Math::Cos(Eegeo::Math::Deg2Rad(angle))) +
                (tangentBasis.GetRow(1) * 50 * Eegeo::Math::Sin(Eegeo::Math::Deg2Rad(angle)));
                
                Eegeo::m33 orientation = GetLookAtOrientationMatrix(centerPoint.ToSingle(), posOrientation.ToSingle(), (m_toEcef-pos).ToSingle().Norm());
                m_debugRenderer.DrawQuad(pos, orientation.GetRow(1) * m_tileLength , orientation.GetRow(0) * m_thickness, orientation.GetRow(2), m_quadColor);
                m_debugRenderer.DrawQuad(pos, orientation.GetRow(1) * m_tileLength , orientation.GetRow(0) * m_thickness*(-1), orientation.GetRow(2), m_quadColor);
                
                lastOrientation = orientation;
                i++;
                angle+=angleIter;
                
            }
            
           
            Eegeo::dv3 arrowPos = centerPoint +
            (tangentBasis.GetRow(2) * radius * Eegeo::Math::Cos(Eegeo::Math::Deg2Rad(angle))) +
            (tangentBasis.GetRow(1) * radius * Eegeo::Math::Sin(Eegeo::Math::Deg2Rad(angle)));
            m_pRenderable->SetEcefPosition(arrowPos);
            m_pRenderable->SetOrientationEcef(lastOrientation);
            
        }
        
        Eegeo::m33 QuadLine::GetLookAtOrientationMatrix(const Eegeo::v3& targetPosition, const Eegeo::v3& objectPosition, Eegeo::v3 up){
            Eegeo::v3 delta = targetPosition-objectPosition;
            Eegeo::v3 direction(delta.Norm());
            Eegeo::v3 right = (Eegeo::v3::Cross(up,direction)).Norm();
            up = (Eegeo::v3::Cross(direction, right)).Norm();
            Eegeo::m33 orientation;
            orientation.SetFromBasis(right, up, direction);
            return orientation;
        }

        
        void QuadLine::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
        {
            const float environmentFlatteningScale = m_environmentFlatteningService.GetCurrentScale();
            const Eegeo::Camera::RenderCamera& renderCamera = renderContext.GetRenderCamera();
            
            const Eegeo::m44& viewProjection = renderCamera.GetViewProjectionMatrix();
            const Eegeo::dv3& ecefCameraPosition = renderCamera.GetEcefLocation();
            
            const Eegeo::m44& mvp = m_pRenderable->CalcModelViewProjection(ecefCameraPosition, viewProjection, environmentFlatteningScale);
            m_pRenderable->SetModelViewProjection(mvp);
            
            renderQueue.EnqueueRenderable(m_pRenderable);
            
            DrawQuadLine();
            
        }
    }
}
