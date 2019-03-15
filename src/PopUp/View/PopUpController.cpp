// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PopUpController.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            void PopUpController::OnOpen(double& xPosition, double& yPosition)
            {
                m_view.Open(xPosition, yPosition);
            }

            void PopUpController::OnClose()
            {
                m_view.Close();
            }

            PopUpController::PopUpController(IPopUpView& view,IPopUpViewModel& viewModel)
                : m_view(view)
                , m_viewModel(viewModel)
                , m_viewClosed(this, &PopUpController::OnClose)
                , m_viewOpened(this, &PopUpController::OnOpen)
            {
                m_viewModel.InsertClosedCallback(m_viewClosed);
                m_viewModel.InsertOpenedCallback(m_viewOpened);
            }

            PopUpController::~PopUpController()
            {
                m_viewModel.RemoveOpenedCallback(m_viewOpened);
                m_viewModel.RemoveClosedCallback(m_viewClosed);
            }
        }
    }
}
