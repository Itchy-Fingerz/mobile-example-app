// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Materials
    {
        class IGeometryController
        {
        public:
            virtual ~IGeometryController() { }
            
            virtual void Update(float dt) = 0;
        };
    }
}