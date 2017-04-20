
// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomAlertScreenControl.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace View
        {
            CustomAlertScreenControl::CustomAlertScreenControl(bool initiallyOnScreen, Eegeo::Helpers::TIdentity identity)
                : ScreenControl::View::ScreenControlViewModelBase(initiallyOnScreen)
                , m_identity(identity)
            {
            }

            Eegeo::Helpers::TIdentity CustomAlertScreenControl::GetIdentity() const
            {
                return m_identity;
            }
        }
    }
}
