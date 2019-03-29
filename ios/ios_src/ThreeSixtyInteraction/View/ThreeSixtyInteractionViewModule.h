// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ThreeSixtyInteraction.h"
#include "IThreeSixtyInteractionViewModule.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            class ThreeSixtyInteractionViewModule: public IThreeSixtyInteractionViewModule, private Eegeo::NonCopyable
            {
            private:
                ThreeSixtyInteractionView* m_pView;
                ThreeSixtyInteractionController* m_pController;
                

            public:
                ThreeSixtyInteractionViewModule(IThreeSixtyInteractionViewModel& threeSixtyInteractionViewModel,
                                                ExampleAppMessaging::TMessageBus& messageBus);

                ~ThreeSixtyInteractionViewModule();

                ThreeSixtyInteractionController& GetThreeSixtyInteractionController() const;

                ThreeSixtyInteractionView& GetThreeSixtyInteractionView() const;
                
            };
        }
    }
}
