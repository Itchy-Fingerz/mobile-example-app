// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include <string>

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            class IThreeSixtyInteractionView
            {
            public:
                
                virtual ~IThreeSixtyInteractionView() { };
                
                virtual void Open(std::string url) = 0;
                
                virtual void Close() = 0;
                
                virtual void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
            };
        }
    }
}
