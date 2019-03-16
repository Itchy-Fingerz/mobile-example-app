// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PopUpViewModule.h"
#include "IPopUpViewModel.h"
#include "PopUpView.h"
#include "PopUpController.h"
#include "AndroidAppThreadAssertionMacros.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            PopUpViewModule::PopUpViewModule(AndroidNativeState& nativeState, IPopUpViewModel& popUpViewModel)
            {
                ASSERT_UI_THREAD
                m_pView = Eegeo_NEW(PopUpView)(nativeState);
                m_pController = Eegeo_NEW(PopUpController)(*m_pView, popUpViewModel);
            }

            PopUpViewModule::~PopUpViewModule()
            {
                Eegeo_DELETE(m_pController);
                Eegeo_DELETE(m_pView);
            }

            PopUpController& PopUpViewModule::GetPopUpController() const
            {
                ASSERT_UI_THREAD
                return *m_pController;
            }

            PopUpView& PopUpViewModule::GetPopUpView() const
            {
                ASSERT_UI_THREAD
                return *m_pView;
            }
        }
    }
}
