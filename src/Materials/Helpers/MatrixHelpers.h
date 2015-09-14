// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace Materials
    {
        namespace MatrixHelpers
        {
            void CreatePlanarReflectionMatrix(Eegeo::m44& reflectionMatrix, const Eegeo::v3& point, const Eegeo::v3& normal);
        }
    }
}