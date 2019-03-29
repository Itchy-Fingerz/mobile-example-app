// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        class ThreeSixtyInteractionMessage
        {
        private:
            std::string m_url;
        public:
            ThreeSixtyInteractionMessage(std::string url);
            std::string GetUrl() const;
        };
    }
}
