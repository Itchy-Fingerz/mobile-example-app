// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"

#include <string>
#include <map>

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            class IPopUpViewModel
            {
            public:
                virtual ~IPopUpViewModel() { }

                virtual void Open(double xPosition, double yPosition) = 0;

                virtual void Close() = 0;

                virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback2<double, double>& openedCallback) = 0;

                virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback2<double, double>& openedCallback) = 0;

                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
                
            };
        }
    }
}
