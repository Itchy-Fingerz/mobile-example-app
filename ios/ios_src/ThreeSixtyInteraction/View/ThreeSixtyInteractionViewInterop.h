// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ThreeSixtyInteractionViewIncludes.h"
#include "IThreeSixtyInteractionView.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            class ThreeSixtyInteractionViewInterop : public IThreeSixtyInteractionView, private Eegeo::NonCopyable
            {
            private:
                ThreeSixtyInteractionView* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_callbacks;

            public:
                ThreeSixtyInteractionViewInterop(ThreeSixtyInteractionView* pView);
                
                void Open(std::string url);

                void Close();

                void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback);
                
                void HandleCloseButtonTapped();
                
            };
        }
    }
    
}
