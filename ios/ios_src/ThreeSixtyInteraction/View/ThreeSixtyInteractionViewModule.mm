// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ThreeSixtyInteractionViewModule.h"
#include "IThreeSixtyInteractionViewModel.h"
#include "ThreeSixtyInteractionView.h"
#include "ThreeSixtyInteractionController.h"
#include "ThreeSixtyInteractionViewInterop.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            ThreeSixtyInteractionViewModule::ThreeSixtyInteractionViewModule(IThreeSixtyInteractionViewModel& threeSixtyInteractionViewModel,
                                                                             ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pView = [[ThreeSixtyInteractionView initView] retain];
                m_pController = Eegeo_NEW(ThreeSixtyInteractionController)(*[m_pView getInterop], threeSixtyInteractionViewModel,messageBus);
            }

            ThreeSixtyInteractionViewModule::~ThreeSixtyInteractionViewModule()
            {
                [m_pView release];
                Eegeo_DELETE m_pController;
            }

            ThreeSixtyInteractionController& ThreeSixtyInteractionViewModule::GetThreeSixtyInteractionController() const
            {
                return *m_pController;
            }

            ThreeSixtyInteractionView& ThreeSixtyInteractionViewModule::GetThreeSixtyInteractionView() const
            {
                return *m_pView;
            }
        }
    }
}
