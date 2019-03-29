// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IThreeSixtyInteractionViewModel.h"
#include "CallbackCollection.h"
#include "Reaction.h"
#include "ThreeSixtyInteraction.h"
#include <sstream>
#include "ThreeSixtyInteractionOpenableControl.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            class ThreeSixtyInteractionViewModel : public IThreeSixtyInteractionViewModel, private Eegeo::NonCopyable
            {
                Eegeo::Helpers::CallbackCollection1<std::string&> m_openedCallbacks;
                Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
                ThreeSixtyInteractionOpenableControl m_openable;


            public:
                ThreeSixtyInteractionViewModel(Eegeo::Helpers::TIdentity identity);
                ~ThreeSixtyInteractionViewModel();
                
                bool IsOpen() const;
                void Open(std::string url);
                void Close();
                
                OpenableControl::View::IOpenableControlViewModel& GetOpenableControl();
                
                void InsertOpenedCallback(Eegeo::Helpers::ICallback1<std::string&>& openedCallback);
                void RemoveOpenedCallback(Eegeo::Helpers::ICallback1<std::string&>& openedCallback);
                void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);
            };
        }
    }
}
