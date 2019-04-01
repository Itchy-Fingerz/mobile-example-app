// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "ThreeSixtyInteraction.h"
#include "ThreeSixtyInteractionViewIncludes.h"
#include "IThreeSixtyInteractionViewModule.h"
#include "IMetricsService.h"
#include "BidirectionalBus.h"
#include "ILocationProvider.h"
#include "ICameraTransitionController.h"
#include "InteriorsCameraController.h"
#include "GlobeCameraController.h"
#include "IPopUpViewModel.h"

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
                ThreeSixtyInteractionViewModule(
                    AndroidNativeState& nativeState,
                    IThreeSixtyInteractionViewModel& threeSixtyInteractionViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~ThreeSixtyInteractionViewModule();

                ThreeSixtyInteractionController& GetThreeSixtyInteractionController() const;
                ThreeSixtyInteractionView& GetThreeSixtyInteractionView() const;
            };
        }
    }
}
