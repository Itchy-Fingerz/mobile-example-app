// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomAlertViewModel.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace View
        {
            CustomAlertViewModel::CustomAlertViewModel(Eegeo::Helpers::TIdentity identity,
                    bool initiallyOnScreen)
                : m_screenControl(initiallyOnScreen, identity)
            {

            }

            ScreenControl::View::IScreenControlViewModel& CustomAlertViewModel::GetScreenControlViewModel()
            {
                return m_screenControl;
            }

            Eegeo::Helpers::TIdentity CustomAlertViewModel::GetIdentity() const
            {
                return m_screenControl.GetIdentity();
            }

            void CustomAlertViewModel::AddToScreen()
            {
                m_screenControl.AddToScreen();
            }

            void CustomAlertViewModel::RemoveFromScreen()
            {
                m_screenControl.RemoveFromScreen();
            }

            void CustomAlertViewModel::UpdateOnScreenState(float onScreenState)
            {
                m_screenControl.UpdateOnScreenState(onScreenState);
            }

            void CustomAlertViewModel::InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenControl.InsertOnScreenStateChangedCallback(callback);
            }

            void CustomAlertViewModel::RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback)
            {
                m_screenControl.RemoveOnScreenStateChangedCallback(callback);
            }

            bool CustomAlertViewModel::IsFullyOffScreen() const
            {
                return m_screenControl.IsFullyOffScreen();
            }

            bool CustomAlertViewModel::IsFullyOnScreen() const
            {
                return m_screenControl.IsFullyOnScreen();
            }

            float CustomAlertViewModel::OnScreenState() const
            {
                return m_screenControl.OnScreenState();
            }
            
            bool CustomAlertViewModel::IsAddedToScreen() const
            {
                return m_screenControl.IsAddedToScreen();
            }

        }
    }
}
