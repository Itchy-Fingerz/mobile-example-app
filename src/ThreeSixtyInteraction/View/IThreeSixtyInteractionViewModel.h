// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include <string>
#include "OpenableControlViewModelBase.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            class IThreeSixtyInteractionViewModel
            {
            public:
                virtual ~IThreeSixtyInteractionViewModel() { }

                virtual bool IsOpen() const = 0;

                virtual void Open(std::string url) = 0;

                virtual void Close() = 0;
                
                virtual OpenableControl::View::IOpenableControlViewModel& GetOpenableControl() = 0;

                virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback1<std::string&>& openedCallback) = 0;
                
                virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback1<std::string&>& openedCallback) = 0;
                
                virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

                virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
                
            };
        }
    }
}
