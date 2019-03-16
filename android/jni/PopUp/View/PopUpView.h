// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IPopUpView.h"
#include "AndroidNativeState.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            class PopUpView : public IPopUpView, private Eegeo::NonCopyable
            {
            private:
                AndroidNativeState& m_nativeState;
                jclass m_uiViewClass;
                jobject m_uiView;

            public:
                PopUpView(AndroidNativeState& nativeState);

                ~PopUpView();

                void Open(double x, double y);

                void Close();
            };
        }
    }

}
