// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuStateChangedMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        DirectionsMenuStateChangedMessage::DirectionsMenuStateChangedMessage(DirectionsMenuStage stage, bool close, bool specialOffers)
        : m_stage(stage)
        , m_closeForWorldPin(close)
        , m_closeForSpecialOffers(specialOffers)
        {
        }
        
        const bool DirectionsMenuStateChangedMessage::GetCloseForWorldPin() const
        {
            return m_closeForWorldPin;
        }

        const DirectionsMenuStage& DirectionsMenuStateChangedMessage::GetDirectionsMenuStage() const
        {
            return m_stage;
        }
        const bool DirectionsMenuStateChangedMessage::GetSpecialOffersFlag() const
        {
            return m_closeForSpecialOffers;
        }

    }
}
