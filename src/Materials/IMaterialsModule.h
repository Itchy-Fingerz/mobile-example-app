// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MaterialsIncludes.h"

#include <vector>

namespace ExampleApp
{
    namespace Materials
    {
        class IMaterialsModule
        {
        public:
            virtual ~IMaterialsModule() { }
            
            virtual IGeometryController& GetGeometryController() const = 0;
        };
    }
}