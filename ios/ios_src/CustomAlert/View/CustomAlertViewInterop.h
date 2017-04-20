// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICustomAlertView.h"
#include "CustomAlert.h"
#include "CustomAlertView.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace View
        {
            class CustomAlertViewInterop : public ICustomAlertView
            {
            private:
                
                CustomAlertView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_callbacks;
                Eegeo::Helpers::CallbackCollection1<const bool> m_showHideOfferCallbacks;

            public:
                
                CustomAlertViewInterop(CustomAlertView* pView);
                
                void OnSelected(){}
                
                void InsertSelectedCallback(Eegeo::Helpers::ICallback0& callback)  {}
                
                void RemoveSelectedCallback(Eegeo::Helpers::ICallback0& callback) {}
                
                void InsertShowHideOfferCallback(Eegeo::Helpers::ICallback1<const bool>& callback);
                
                void RemoveShowHideOfferCallback(Eegeo::Helpers::ICallback1<const bool>& callback);
                

              
                void SetOnScreenStateToIntermediateValue(float value) {}
                void SetFullyOnScreen() { m_pView.hidden = false;}
                void SetFullyOffScreen() {m_pView.hidden = true;}
                
                void OnAccepet();
                void OnCancel();
                
            };
        }
    }
}
