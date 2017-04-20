// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "GeometryHelpers.h"
#include "Bounds.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace View
        {
            const int faces = 6;
            const int pointsPerFace = 4;
          
            
            Eegeo::v3 faceNormals[faces] =
            {
                Eegeo::v3(1.f, 0.f, 0.f),
                Eegeo::v3(0.f, 0.f, 1.f),
                Eegeo::v3(-1.f, 0.f, 0.f),
                Eegeo::v3(0.f, 0.f, -1.f),
                Eegeo::v3(0.f, 1.f, 0.f),
                Eegeo::v3(0.f, -1.f, 0.f)
            };
            
           
            
            int pointIndices[faces*pointsPerFace] =
            {
                1, 0, 3, 2,
            };
            
            
            Eegeo::Geometry::Bounds2D uvRects[] =
            {
                Eegeo::Geometry::Bounds2D( Eegeo::v2::Zero(), Eegeo::v2::One()),
            };

            
            void BuildBox(const Eegeo::v3& halfDimensions, std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices, int zfactor, int yfactor)
            {
                out_vertices.clear();
                out_triangleIndices.clear();
                out_vertices.reserve(pointsPerFace*faces);
                out_triangleIndices.reserve(faces*3*2);
                
                Eegeo::v3 points[8] =
                {
                    Eegeo::v3(halfDimensions.x, halfDimensions.y*yfactor, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, halfDimensions.y*yfactor, -halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y*yfactor, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y*yfactor, -halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, halfDimensions.y*yfactor, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, halfDimensions.y*yfactor, -halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y*yfactor, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y*yfactor, -halfDimensions.z*zfactor),
                };
                
                const Eegeo::v3& faceNormal = faceNormals[0];
                
                const Eegeo::Geometry::Bounds2D& uvRect = uvRects[0];
                
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
            
            void BuildVideoBox(const Eegeo::v3& halfDimensions, std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices, int zfactor)
            {
                out_vertices.clear();
                out_triangleIndices.clear();
                out_vertices.reserve(pointsPerFace*faces);
                out_triangleIndices.reserve(faces*3*2);
                
                Eegeo::v3 points[8] =
                {
                    Eegeo::v3(halfDimensions.x, halfDimensions.y, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, halfDimensions.y, -halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y, -halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, halfDimensions.y, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, halfDimensions.y, -halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y, -halfDimensions.z*zfactor),
                };
                
                int pointIndices[faces*pointsPerFace] =
                {
                    3, 2, 1, 0,
                };
                
                
                const Eegeo::v3& faceNormal = faceNormals[0];
                
                const Eegeo::Geometry::Bounds2D& uvRect = uvRects[0];
                
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
            
            void BuildSpinnerBox(const Eegeo::v3& halfDimensions, std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices, int zfactor)
            {
                out_vertices.clear();
                out_triangleIndices.clear();
                out_vertices.reserve(pointsPerFace*faces);
                out_triangleIndices.reserve(faces*3*2);
                
                Eegeo::v3 points[8] =
                {
                    Eegeo::v3(halfDimensions.x, halfDimensions.y, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, halfDimensions.y, -halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y, -halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, halfDimensions.y, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, halfDimensions.y, -halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y, halfDimensions.z*zfactor),
                    Eegeo::v3(halfDimensions.x, -halfDimensions.y, -halfDimensions.z*zfactor),
                };
                
                int pointIndices[faces*pointsPerFace] =
                {
                    1, 0, 3, 2,
                };
                
                
                const Eegeo::v3& faceNormal = faceNormals[0];
                
                const Eegeo::Geometry::Bounds2D& uvRect = uvRects[0];
                
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
