// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MatrixHelpers.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace MatrixHelpers
        {
            void CreatePlanarReflectionMatrix(Eegeo::m44& reflectionMatrix, const Eegeo::v3& point, const Eegeo::v3& normal)
            {
                float pDotN = Eegeo::v3::Dot(point, normal);
                
                reflectionMatrix.SetRow(0,
                                        Eegeo::v4(1.0f - 2 * normal.x * normal.x,
                                                  -2.0f * normal.x * normal.y,
                                                  -2.0f * normal.x * normal.z,
                                                  0.0f));
                
                reflectionMatrix.SetRow(1,
                                        Eegeo::v4(-2.0f * normal.x * normal.y,
                                                  1.0f - 2 * normal.y * normal.y,
                                                  -2.0f * normal.y * normal.z,
                                                  0.0f));
                
                reflectionMatrix.SetRow(2,
                                        Eegeo::v4(-2.0f * normal.x * normal.z,
                                                  -2.0f * normal.y * normal.z,
                                                  1.0f - 2 * normal.z * normal.z,
                                                  0.0f));
                
                reflectionMatrix.SetRow(3,
                                        Eegeo::v4(2.0f * pDotN * normal.x,
                                                  2.0f * pDotN * normal.y,
                                                  2.0f * pDotN * normal.z,
                                                  1.0f));
            }
        }
    }
}
