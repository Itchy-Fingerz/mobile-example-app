// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomAlertViewInterop.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace View
        {
            CustomAlertViewInterop::CustomAlertViewInterop(CustomAlertView* pView)
            : m_pView(pView)
            {
                
            }
            
            
            void CustomAlertViewInterop::OnAccepet()
            {
                bool value = true;
                m_showHideOfferCallbacks.ExecuteCallbacks(value);
            }
            void CustomAlertViewInterop::OnCancel()
            {
                bool value = false;
                m_showHideOfferCallbacks.ExecuteCallbacks(value);
            }
            

            
            void CustomAlertViewInterop::InsertShowHideOfferCallback(Eegeo::Helpers::ICallback1<const bool>& callback)
            {
                m_showHideOfferCallbacks.AddCallback(callback);
            }
            
            void CustomAlertViewInterop::RemoveShowHideOfferCallback(Eegeo::Helpers::ICallback1<const bool>& callback)
            {
                m_showHideOfferCallbacks.RemoveCallback(callback);
            }
        }
    }
}
