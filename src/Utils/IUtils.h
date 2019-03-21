// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Utils
    {
        class IUtils
        {
        public:
            virtual ~IUtils() {}
            
            virtual void OpenARApplication() = 0;
        };
    }
}
