// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "PopUp.h"
#include "ICallback.h"
#include "IPopUpViewModel.h"
#include "IPopUpView.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            class PopUpController : private Eegeo::NonCopyable
            {
            private:
                IPopUpView& m_view;
                IPopUpViewModel& m_viewModel;

                Eegeo::Helpers::TCallback2<PopUpController, double, double> m_viewOpened;
                Eegeo::Helpers::TCallback0<PopUpController> m_viewClosed;

                void OnOpen(double& xPosition, double& yPosition);
                void OnClose();
                void OnCloseTapped();
            
            public:
                PopUpController(IPopUpView& view, IPopUpViewModel& viewModel);

                ~PopUpController();
            };
        }
    }
}
