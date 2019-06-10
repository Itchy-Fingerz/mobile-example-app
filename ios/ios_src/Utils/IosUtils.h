// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IUtils.h"

namespace ExampleApp
{
    namespace Utils
    {
        class IosUtils: public IUtils, private Eegeo::NonCopyable
        {
        public:
            IosUtils();
            
            ~IosUtils();
            
            void OpenARApplication();
            void notifyAppNotInstalled();
            void notifyAppNotTrusted();
        };
    }
}

