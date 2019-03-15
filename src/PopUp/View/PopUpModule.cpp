// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PopUpModule.h"
#include "PopUpViewModel.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            PopUpModule::PopUpModule()
            {
                m_pPopUpViewModel = Eegeo_NEW(PopUpViewModel)();
            }

            PopUpModule::~PopUpModule()
            {
                Eegeo_DELETE m_pPopUpViewModel;
            }

            IPopUpViewModel& PopUpModule::GetPopUpViewModel() const
            {
                return *m_pPopUpViewModel;
            }
        }
    }
}
