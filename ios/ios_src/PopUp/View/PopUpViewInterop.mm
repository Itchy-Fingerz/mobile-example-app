// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PopUpViewInterop.h"
#include "PopUpView.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            PopUpViewInterop::PopUpViewInterop(PopUpView* pView) : m_pView(pView)
            {
            }

            void PopUpViewInterop::Open(double x, double y)
            {
                [m_pView setPosition:x ndY:y];
                [m_pView setFullyActive];
            }

            void PopUpViewInterop::Close()
            {
                [m_pView setFullyInactive];
            }
        }
    }
}
