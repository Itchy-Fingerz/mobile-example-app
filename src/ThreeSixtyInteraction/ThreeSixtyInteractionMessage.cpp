// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ThreeSixtyInteractionMessage.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        ThreeSixtyInteractionMessage::ThreeSixtyInteractionMessage(std::string url)
        : m_url(url)
        {
        }
        std::string ThreeSixtyInteractionMessage::GetUrl() const
        {
            return m_url;
        }

    }
}
