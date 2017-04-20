// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomAlertController.h"
#include "IAppModeModel.h"
#include "ShowOfferHighlightMessage.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace View
        {
            void CustomAlertController::OnSelected()
            {
            }

            void CustomAlertController::OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state)
            {
            }
            
            void CustomAlertController::OnHandleSetVisibility(const SetCustomAlertVisibilityMessage& message)
            {
                if(message.GetShouldSetVisible())
                {
                    m_view.SetFullyOnScreen();
                }
                else
                {
                    m_view.SetFullyOffScreen();
                }
            }
            
            void CustomAlertController::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
            }
            
            void CustomAlertController::OnOfferShowHideCallBackHandler(const bool &shoulShow)
            {
                if (shoulShow)
                {
                    m_messageBus.Publish(ExampleApp::BillBoards::ShowOfferHighlightMessage());
                }
            }
            
            CustomAlertController::CustomAlertController(
                ICustomAlertViewModel& viewModel,
                ICustomAlertView& view,
                ExampleAppMessaging::TMessageBus& messageBus
            )
            : m_viewModel(viewModel)
            , m_view(view)
            , m_messageBus(messageBus)
            , m_selectedCallback(this, &CustomAlertController::OnSelected)
            , m_viewStateCallback(this, &CustomAlertController::OnViewStateChangeScreenControl)
            , m_setVisibilityHandler(this, &CustomAlertController::OnHandleSetVisibility)
            , m_appModeChangedHandler(this, &CustomAlertController::OnAppModeChanged)
            , m_offerShowHideHandler(this, &CustomAlertController::OnOfferShowHideCallBackHandler)
            {
                m_view.InsertSelectedCallback(m_selectedCallback);
                m_viewModel.InsertOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.InsertShowHideOfferCallback(m_offerShowHideHandler);
                m_messageBus.SubscribeUi(m_setVisibilityHandler);
                m_messageBus.SubscribeUi(m_appModeChangedHandler);
            }

            CustomAlertController::~CustomAlertController()
            {
                m_messageBus.UnsubscribeUi(m_setVisibilityHandler);
                m_messageBus.UnsubscribeUi(m_appModeChangedHandler);
                m_viewModel.RemoveOnScreenStateChangedCallback(m_viewStateCallback);
                m_view.RemoveSelectedCallback(m_selectedCallback);
            }
        }
    }
}
