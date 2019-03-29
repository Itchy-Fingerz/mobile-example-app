// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ThreeSixtyInteractionViewInterop.h"
#include "ThreeSixtyInteractionView.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            ThreeSixtyInteractionViewInterop::ThreeSixtyInteractionViewInterop(ThreeSixtyInteractionView* pView)
            : m_pView(pView)
            {

            }

            void ThreeSixtyInteractionViewInterop::Open(std::string url)
            {
                [m_pView setContent:url];
                [m_pView setFullyActive];
            }

            void ThreeSixtyInteractionViewInterop::Close()
            {
                [m_pView setFullyInactive];
            }
           
            void ThreeSixtyInteractionViewInterop::InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.AddCallback(callback);
            }

            void ThreeSixtyInteractionViewInterop::RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                m_callbacks.RemoveCallback(callback);
            }
            
            void ThreeSixtyInteractionViewInterop::HandleCloseButtonTapped()
            {
                m_callbacks.ExecuteCallbacks();
            }
        }
    }
}
