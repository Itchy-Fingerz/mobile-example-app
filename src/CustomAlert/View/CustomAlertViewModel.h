// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "IIdentity.h"
#include "CustomAlertScreenControl.h"
#include "ICustomAlertViewModel.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace View
        {
            class CustomAlertViewModel : public ICustomAlertViewModel, private Eegeo::NonCopyable
            {
            public:

                CustomAlertViewModel(Eegeo::Helpers::TIdentity identity,
                                       bool isInitiallyOnScreen);

                Eegeo::Helpers::TIdentity GetIdentity() const;

                void AddToScreen();

                void RemoveFromScreen();

                void UpdateOnScreenState(float onScreenState);

                void InsertOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback);

                void RemoveOnScreenStateChangedCallback(Eegeo::Helpers::ICallback2<ScreenControl::View::IScreenControlViewModel&, float>& callback);

                bool IsFullyOffScreen() const;

                bool IsFullyOnScreen() const;

                float OnScreenState() const;
                
                bool IsAddedToScreen() const;

                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel();

            private:
                CustomAlertScreenControl m_screenControl;
            };
        }
    }
}
