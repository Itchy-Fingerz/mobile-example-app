// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "TriangleGeometryHelpers.h"
#include "Bounds.h"


namespace ExampleApp
{
    namespace PointingQuadRadialLine
    {
        namespace TriangleGeometryHelpers
        {
            void BuildBox(const Eegeo::v3& halfDimensions, std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices)
            {
                const int pointsPerFace = 4;
                out_vertices.clear();
                out_triangleIndices.clear();
                out_vertices.reserve(pointsPerFace);
                out_triangleIndices.reserve(3*2);
                
                Eegeo::v3 faceNormals[1] =
                {
                    Eegeo::v3(0.f, 0.f, 0.f)
                };
                
                Eegeo::v3 points[4] =
                {
                    Eegeo::v3(0, halfDimensions.y, 0),
                    Eegeo::v3(0, halfDimensions.y, 0),
                    Eegeo::v3(-halfDimensions.x, -halfDimensions.y, 0),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y, 0)
                };
                
                int pointIndices[pointsPerFace] =
                {
                    1, 0, 3, 2
                };
                
                
                Eegeo::Geometry::Bounds2D uvRects[] =
                {
                    Eegeo::Geometry::Bounds2D(Eegeo::v2(0.0f, 0.0f), Eegeo::v2(0.5f, 0.5f))
                };
                
                
                for (int i = 0; i < 1; ++i)
                {
                    const Eegeo::v3& faceNormal = faceNormals[i];
                    
                    const Eegeo::Geometry::Bounds2D& uvRect = uvRects[i];
                    
                    //                u16 offset = static_cast<u16>(i*pointsPerFace);
                    out_vertices.push_back(Vertex(points[pointIndices[0]], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.max.y)));
                    out_vertices.push_back(Vertex(points[pointIndices[1]], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.max.y)));
                    out_vertices.push_back(Vertex(points[pointIndices[2]], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.min.y)));
                    out_vertices.push_back(Vertex(points[pointIndices[3]], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.min.y)));
                    
                    out_triangleIndices.push_back(0);
                    out_triangleIndices.push_back(1);
                    out_triangleIndices.push_back(2);
                    out_triangleIndices.push_back(2);
                    out_triangleIndices.push_back(1);
                    out_triangleIndices.push_back(3);
                }
            }
        }
    }
}