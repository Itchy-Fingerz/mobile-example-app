// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PopUpViewModule.h"
#include "IPopUpViewModel.h"
#include "PopUpView.h"
#include "PopUpViewInterop.h"
#include "PopUpController.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            PopUpViewModule::PopUpViewModule(IPopUpViewModel& popUpViewModel, const Eegeo::Rendering::ScreenProperties& screenProperties)
            {
                m_pView = [[PopUpView alloc] initView:screenProperties.GetPixelScale()];
                m_pController = Eegeo_NEW(PopUpController)(*[m_pView getInterop], popUpViewModel);
            }

            PopUpViewModule::~PopUpViewModule()
            {
                Eegeo_DELETE m_pController;
                [m_pView release];
            }

            PopUpController& PopUpViewModule::GetPopUpController() const
            {
                return *m_pController;
            }

            PopUpView& PopUpViewModule::GetPopUpView() const
            {
                return *m_pView;
            }
        }
    }
}
