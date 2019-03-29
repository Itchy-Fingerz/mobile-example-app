// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ThreeSixtyInteractionOpenableControl.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            ThreeSixtyInteractionOpenableControl::ThreeSixtyInteractionOpenableControl(Eegeo::Helpers::TIdentity identity)
                : OpenableControl::View::OpenableControlViewModelBase()
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity ThreeSixtyInteractionOpenableControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
