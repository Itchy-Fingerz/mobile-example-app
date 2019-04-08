// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ThreeSixtyInteractionViewModule.h"
#include "ThreeSixtyInteraction.h"
#include "ThreeSixtyInteractionView.h"
#include "ThreeSixtyInteractionController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            ThreeSixtyInteractionViewModule::ThreeSixtyInteractionViewModule(
                AndroidNativeState& nativeState,
                IThreeSixtyInteractionViewModel& threeSixtyInteractionViewModel,
                ExampleAppMessaging::TMessageBus& messageBus
            )
            {
                ASSERT_UI_THREAD
                m_pView = Eegeo_NEW(ThreeSixtyInteractionView)(nativeState);
                m_pController = Eegeo_NEW(ThreeSixtyInteractionController)(*m_pView, threeSixtyInteractionViewModel, messageBus);
            }

            ThreeSixtyInteractionViewModule::~ThreeSixtyInteractionViewModule()
            {
                ASSERT_UI_THREAD

                Eegeo_DELETE(m_pController);
                Eegeo_DELETE(m_pView);
            }

            ThreeSixtyInteractionController& ThreeSixtyInteractionViewModule::GetThreeSixtyInteractionController() const
            {
                ASSERT_UI_THREAD
                return *m_pController;
            }

            ThreeSixtyInteractionView& ThreeSixtyInteractionViewModule::GetThreeSixtyInteractionView() const
            {
                ASSERT_UI_THREAD
                return *m_pView;
            }
        }
    }
}
