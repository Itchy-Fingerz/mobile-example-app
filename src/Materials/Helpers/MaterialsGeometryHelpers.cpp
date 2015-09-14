// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MaterialsGeometryHelpers.h"
#include "Bounds.h"
#include "VertexLayout.h"
#include "Mesh.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace GeometryHelpers
        {
            inline PositionNormalUvVertex MakePositionNormalUvVertex(const Eegeo::v3& pos, const Eegeo::v3& norm, const Eegeo::v2& uv)
            {
                PositionNormalUvVertex v;
                v.x = pos.x;
                v.y = pos.y;
                v.z = pos.z;
                v.nx = norm.x;
                v.ny = norm.y;
                v.nz = norm.z;
                v.u = uv.x;
                v.v = uv.y;
                return v;
            }
            
            Eegeo::Rendering::VertexLayouts::VertexLayout* CreatePositionNormalUvVertexLayout()
            {
                using namespace Eegeo::Rendering::VertexLayouts;
                VertexLayout* pLayout = new (VertexLayout)(sizeof(PositionNormalUvVertex));
                
                int positionOffset = offsetof(PositionNormalUvVertex, x);
                pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::Position, 3, GL_FLOAT, positionOffset));
                
                int normalOffset = offsetof(PositionNormalUvVertex, nx);
                pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::Normal, 3, GL_FLOAT, normalOffset));
                
                int uvOffset = offsetof(PositionNormalUvVertex, u);
                pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::UV, 2, GL_FLOAT, uvOffset));
                
                return pLayout;
            }
            
            Eegeo::Rendering::Mesh* CreateLitBoxMesh(const Eegeo::v3& dimensions, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool)
            {
                Eegeo::v3 halfDimensions(dimensions.x * 0.5f, dimensions.y * 0.5f, dimensions.z * 0.5f);
                std::vector<PositionNormalUvVertex> boxVertices;
                std::vector<u16> triangleIndices;
                
                BuildBox(halfDimensions, boxVertices, triangleIndices);
                
                size_t vertexBufferSizeBytes = sizeof(PositionNormalUvVertex) * boxVertices.size();
                size_t indexBufferSizeBytes = sizeof(u16) * triangleIndices.size();
                
                return new (Eegeo::Rendering::Mesh)(vertexLayout,
                                                    glBufferPool,
                                                    boxVertices.data(),
                                                    vertexBufferSizeBytes,
                                                    triangleIndices.data(),
                                                    indexBufferSizeBytes,
                                                    static_cast<u32>(triangleIndices.size()),
                                                    "LitBoxMesh");
            }
            
            Eegeo::Rendering::Mesh* CreateLitPlaneMesh(const Eegeo::v2 &halfDimensions, float uvScale, const Eegeo::m33 &basis, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool)
            {
                std::vector<PositionNormalUvVertex> planeVertices;
                std::vector<u16> triangleIndices;
                
                BuildPlane(halfDimensions, uvScale, basis, planeVertices, triangleIndices);
                
                size_t vertexBufferSizeBytes = sizeof(PositionNormalUvVertex) * planeVertices.size();
                size_t indexBufferSizeBytes = sizeof(u16) * triangleIndices.size();
                
                return new (Eegeo::Rendering::Mesh)(vertexLayout,
                                                    glBufferPool,
                                                    planeVertices.data(),
                                                    vertexBufferSizeBytes,
                                                    triangleIndices.data(),
                                                    indexBufferSizeBytes,
                                                    static_cast<u32>(triangleIndices.size()),
                                                    "LitPlaneMesh");
            }
            
            Eegeo::Rendering::Mesh* CreateLitPlaneMesh(const Eegeo::v2 &halfDimensions, const Eegeo::Geometry::Bounds2D& uvRect, const Eegeo::m33 &basis, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool)
            {
                std::vector<PositionNormalUvVertex> planeVertices;
                std::vector<u16> triangleIndices;
                
                BuildPlane(halfDimensions, uvRect, basis, planeVertices, triangleIndices);
                
                size_t vertexBufferSizeBytes = sizeof(PositionNormalUvVertex) * planeVertices.size();
                size_t indexBufferSizeBytes = sizeof(u16) * triangleIndices.size();
                
                return new (Eegeo::Rendering::Mesh)(vertexLayout,
                                                    glBufferPool,
                                                    planeVertices.data(),
                                                    vertexBufferSizeBytes,
                                                    triangleIndices.data(),
                                                    indexBufferSizeBytes,
                                                    static_cast<u32>(triangleIndices.size()),
                                                    "LitPlaneMesh");
            }
            
            void BuildBox(const Eegeo::v3& halfDimensions, std::vector<PositionNormalUvVertex>& out_vertices, std::vector<u16>& out_triangleIndices)
            {
                const int faces = 6;
                const int pointsPerFace = 4;
                out_vertices.clear();
                out_triangleIndices.clear();
                out_vertices.reserve(pointsPerFace*faces);
                out_triangleIndices.reserve(faces*3*2);
                
                Eegeo::v3 faceNormals[faces] =
                {
                    Eegeo::v3(1.f, 0.f, 0.f),
                    Eegeo::v3(0.f, 0.f, 1.f),
                    Eegeo::v3(-1.f, 0.f, 0.f),
                    Eegeo::v3(0.f, 0.f, -1.f),
                    Eegeo::v3(0.f, 1.f, 0.f),
                    Eegeo::v3(0.f, -1.f, 0.f)
                };
                
                Eegeo::v3 points[8] =
                {
                    Eegeo::v3(halfDimensions.x, halfDimensions.y, halfDimensions.z),
                    Eegeo::v3(halfDimensions.x, halfDimensions.y, -halfDimensions.z),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y, halfDimensions.z),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y, -halfDimensions.z),
                    Eegeo::v3(-halfDimensions.x, halfDimensions.y, halfDimensions.z),
                    Eegeo::v3(-halfDimensions.x, halfDimensions.y, -halfDimensions.z),
                    Eegeo::v3(-halfDimensions.x, -halfDimensions.y, halfDimensions.z),
                    Eegeo::v3(-halfDimensions.x, -halfDimensions.y, -halfDimensions.z),
                };
                
                int pointIndices[faces*pointsPerFace] =
                {
                    1, 0, 3, 2,
                    0, 4, 2, 6,
                    4, 5, 6, 7,
                    5, 1, 7, 3,
                    4, 0, 5, 1,
                    7, 3, 6, 2,
                };
                
                
                Eegeo::Geometry::Bounds2D uvRects[] =
                {
                    Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),    // +ve x
                    Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),    // +ve z
                    Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),    // -ve x
                    Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),    // -ve z
                    Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),    // +ve y
                    Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),    // -ve y
                };
                
                
                for (int i = 0; i < 6; ++i)
                {
                    const Eegeo::v3& faceNormal = faceNormals[i];
                    
                    const Eegeo::Geometry::Bounds2D& uvRect = uvRects[i];
                    
                    u16 offset = static_cast<u16>(i*pointsPerFace);
                    out_vertices.push_back(MakePositionNormalUvVertex(points[pointIndices[offset + 0]], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.max.y)));
                    out_vertices.push_back(MakePositionNormalUvVertex(points[pointIndices[offset + 1]], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.max.y)));
                    out_vertices.push_back(MakePositionNormalUvVertex(points[pointIndices[offset + 2]], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.min.y)));
                    out_vertices.push_back(MakePositionNormalUvVertex(points[pointIndices[offset + 3]], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.min.y)));
                    
                    out_triangleIndices.push_back(offset + 0);
                    out_triangleIndices.push_back(offset + 1);
                    out_triangleIndices.push_back(offset + 2);
                    out_triangleIndices.push_back(offset + 2);
                    out_triangleIndices.push_back(offset + 1);
                    out_triangleIndices.push_back(offset + 3);
                }
            }
            
            void BuildPlane(const Eegeo::v2& dimensions, float uvScale, const Eegeo::m33& basis, std::vector<PositionNormalUvVertex>& out_vertices, std::vector<u16>& out_triangleIndices)
            {
                Eegeo::v2 halfDimensions = dimensions * 0.5f;
                out_vertices.clear();
                out_triangleIndices.clear();
                out_vertices.reserve(4);
                out_triangleIndices.reserve(6);
                
                Eegeo::v3 faceNormal = Eegeo::v3::Mul(Eegeo::v3(0.0f, 0.0f, 1.0f), basis);
                
                Eegeo::v3 points[4] =
                {
                    Eegeo::v3::Mul(Eegeo::v3(halfDimensions.x, halfDimensions.y, 0.0f), basis),
                    Eegeo::v3::Mul(Eegeo::v3(-halfDimensions.x, halfDimensions.y, 0.0f), basis),
                    Eegeo::v3::Mul(Eegeo::v3(halfDimensions.x, -halfDimensions.y, 0.0f), basis),
                    Eegeo::v3::Mul(Eegeo::v3(-halfDimensions.x, -halfDimensions.y, 0.0f), basis)
                };
                
                int pointIndices[4] =
                {
                    1, 3, 0, 2
                };
                
                Eegeo::Geometry::Bounds2D uvRect(Eegeo::v2::Zero(), Eegeo::v2(dimensions.x / uvScale, dimensions.y / uvScale));
                
                out_vertices.push_back(MakePositionNormalUvVertex(points[pointIndices[0]], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.max.y)));
                out_vertices.push_back(MakePositionNormalUvVertex(points[pointIndices[1]], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.max.y)));
                out_vertices.push_back(MakePositionNormalUvVertex(points[pointIndices[2]], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.min.y)));
                out_vertices.push_back(MakePositionNormalUvVertex(points[pointIndices[3]], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.min.y)));
                
                out_triangleIndices.push_back(0);
                out_triangleIndices.push_back(1);
                out_triangleIndices.push_back(3);
                out_triangleIndices.push_back(3);
                out_triangleIndices.push_back(2);
                out_triangleIndices.push_back(0);
            }
            
            void BuildPlane(const Eegeo::v2& dimensions, const Eegeo::Geometry::Bounds2D& uvRect, const Eegeo::m33& basis, std::vector<PositionNormalUvVertex>& out_vertices, std::vector<u16>& out_triangleIndices)
            {
                Eegeo::v2 halfDimensions = dimensions * 0.5f;
                out_vertices.clear();
                out_triangleIndices.clear();
                out_vertices.reserve(4);
                out_triangleIndices.reserve(6);
                
                Eegeo::v3 faceNormal = Eegeo::v3::Mul(Eegeo::v3(0.0f, 0.0f, 1.0f), basis);
                
                Eegeo::v3 points[4] =
                {
                    Eegeo::v3::Mul(Eegeo::v3(halfDimensions.x, halfDimensions.y, 0.0f), basis),
                    Eegeo::v3::Mul(Eegeo::v3(-halfDimensions.x, halfDimensions.y, 0.0f), basis),
                    Eegeo::v3::Mul(Eegeo::v3(halfDimensions.x, -halfDimensions.y, 0.0f), basis),
                    Eegeo::v3::Mul(Eegeo::v3(-halfDimensions.x, -halfDimensions.y, 0.0f), basis)
                };
                
                out_vertices.push_back(MakePositionNormalUvVertex(points[0], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.max.y)));
                out_vertices.push_back(MakePositionNormalUvVertex(points[1], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.max.y)));
                out_vertices.push_back(MakePositionNormalUvVertex(points[2], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.min.y)));
                out_vertices.push_back(MakePositionNormalUvVertex(points[3], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.min.y)));
                
                out_triangleIndices.push_back(0);
                out_triangleIndices.push_back(1);
                out_triangleIndices.push_back(3);
                out_triangleIndices.push_back(3);
                out_triangleIndices.push_back(2);
                out_triangleIndices.push_back(0);
            }
        }
    }
}