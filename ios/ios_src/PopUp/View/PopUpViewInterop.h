// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "PopUpViewIncludes.h"
#include "IPopUpView.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            class PopUpViewInterop : public IPopUpView, private Eegeo::NonCopyable
            {
            private:
                PopUpView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_callbacks;
                Eegeo::Helpers::CallbackCollection0 m_hiddenTextCallbacks;

            public:
                PopUpViewInterop(PopUpView* pView);

                void Open(double x, double y);

                void Close();
            };
        }
    }

}
