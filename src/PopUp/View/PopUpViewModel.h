// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IPopUpViewModel.h"
#include "CallbackCollection.h"
#include "Reaction.h"
#include "PopUp.h"
#include <sstream>

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            class PopUpViewModel : public IPopUpViewModel, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::CallbackCollection2<double, double> m_openedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;

            public:
                PopUpViewModel();

                ~PopUpViewModel();
                
                void Open(double xPosition, double yPosition);
                void Close();

                void InsertOpenedCallback(Eegeo::Helpers::ICallback2<double, double>& openedCallback);
                void RemoveOpenedCallback(Eegeo::Helpers::ICallback2<double, double>& openedCallback);
                void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
            };
        }
    }
}
