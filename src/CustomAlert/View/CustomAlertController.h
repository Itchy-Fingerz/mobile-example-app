// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "CustomAlert.h"
#include "ICustomAlertView.h"
#include "ICustomAlertViewModel.h"
#include "ApplyScreenControl.h"
#include "MyPinCreationStateChangedMessage.h"
#include "SetCustomAlertVisibilityMessage.h"
#include "AppModes.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace View
        {
            class CustomAlertController : private Eegeo::NonCopyable
            {
            private:
                ICustomAlertViewModel& m_viewModel;
                ICustomAlertView& m_view;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                bool m_isCustomAlertShown;

                Eegeo::Helpers::TCallback0<CustomAlertController> m_selectedCallback;
                Eegeo::Helpers::TCallback2<CustomAlertController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                Eegeo::Helpers::TCallback1<CustomAlertController, const SetCustomAlertVisibilityMessage&> m_setVisibilityHandler;
                Eegeo::Helpers::TCallback1<CustomAlertController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
                Eegeo::Helpers::TCallback1<CustomAlertController, const bool> m_offerShowHideHandler;


                void OnSelected();

                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel& viewModel, float& state);
                
                void OnHandleSetVisibility(const SetCustomAlertVisibilityMessage& message);
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
                void OnOfferShowHideCallBackHandler(const bool& shoulShow);

            public:
                CustomAlertController(
                    ICustomAlertViewModel& viewModel,
                    ICustomAlertView& view,
                    ExampleAppMessaging::TMessageBus& messageBus);

                ~CustomAlertController();
                
                bool IsAlertShown()
                {
                    return m_isCustomAlertShown;
                }
            };
        }
    }
}
