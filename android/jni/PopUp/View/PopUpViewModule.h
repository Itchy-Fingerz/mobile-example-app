// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "PopUp.h"
#include "IPopUpViewModule.h"
#include "IMetricsService.h"
#include "Rendering.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            class PopUpViewModule: public IPopUpViewModule, private Eegeo::NonCopyable
            {
            private:
                PopUpView* m_pView;
                PopUpController* m_pController;

            public:
                PopUpViewModule(AndroidNativeState& nativeState, IPopUpViewModel& popUpViewModel);

                ~PopUpViewModule();

                PopUpController& GetPopUpController() const;

                PopUpView& GetPopUpView() const;
            };
        }
    }
}
