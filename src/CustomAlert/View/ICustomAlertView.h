// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IScreenControlView.h"
#include "ICallback.h"
#include "CustomAlert.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace View
        {
            class ICustomAlertView : public ScreenControl::View::IScreenControlView
            {
            public:
                virtual ~ICustomAlertView() { };
                
                virtual void OnSelected() = 0;
                virtual void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                virtual void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
                
                virtual void InsertShowHideOfferCallback(Eegeo::Helpers::ICallback1<const bool>& callback) = 0;
                
                virtual void RemoveShowHideOfferCallback(Eegeo::Helpers::ICallback1<const bool>& callback) = 0;
                
                
                virtual void OnAccepet() = 0;
                virtual void OnCancel() = 0;
            };
        }
    }
}
