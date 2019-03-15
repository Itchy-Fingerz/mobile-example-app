// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "PopUp.h"
#include "IPopUpModule.h"
#include "PopUpViewModel.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            class PopUpModule : public IPopUpModule, private Eegeo::NonCopyable
            {
                PopUpViewModel* m_pPopUpViewModel;

            public:
                PopUpModule();

                ~PopUpModule();

                IPopUpViewModel& GetPopUpViewModel() const;

            };
        }
    }
}
