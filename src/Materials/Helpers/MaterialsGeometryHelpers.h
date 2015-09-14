// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMathDecl.h"
#include "Geometry.h"
#include "Rendering.h"
#include <vector>

namespace ExampleApp
{
    namespace Materials
    {
        namespace GeometryHelpers
        {
            struct PositionNormalUvVertex
            {
                float x;
                float y;
                float z;
                float nx;
                float ny;
                float nz;
                float u;
                float v;
            };
            
            inline PositionNormalUvVertex MakePositionNormalUvVertex(const Eegeo::v3& pos, const Eegeo::v3& norm, const Eegeo::v2& uv);
            
            Eegeo::Rendering::VertexLayouts::VertexLayout* CreatePositionNormalUvVertexLayout();
            
            Eegeo::Rendering::Mesh* CreateLitBoxMesh(const Eegeo::v3& dimensions, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool);
            
            Eegeo::Rendering::Mesh* CreateLitPlaneMesh(const Eegeo::v2 &halfDimensions, float uvScale, const Eegeo::m33 &basis, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool);
            
            Eegeo::Rendering::Mesh* CreateLitPlaneMesh(const Eegeo::v2 &halfDimensions, const Eegeo::Geometry::Bounds2D& uvRect, const Eegeo::m33 &basis, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool);
            
            void BuildBox(const Eegeo::v3& halfDimensions, std::vector<PositionNormalUvVertex>& out_vertices, std::vector<u16>& out_triangleIndices);
            
            void BuildPlane(const Eegeo::v2& dimensions, float uvScale, const Eegeo::m33& basis, std::vector<PositionNormalUvVertex>& out_vertices, std::vector<u16>& out_triangleIndices);
            
            void BuildPlane(const Eegeo::v2& dimensions, const Eegeo::Geometry::Bounds2D& uvRect, const Eegeo::m33& basis, std::vector<PositionNormalUvVertex>& out_vertices, std::vector<u16>& out_triangleIndices);
        }
    }
}