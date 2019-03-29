// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ThreeSixtyInteraction.h"
#include "ICallback.h"
#include "IThreeSixtyInteractionViewModel.h"
#include "IThreeSixtyInteractionView.h"
#include "BidirectionalBus.h"
#include "ThreeSixtyInteractionMessage.h"

namespace ExampleApp
{
    namespace ThreeSixtyInteraction
    {
        namespace View
        {
            class ThreeSixtyInteractionController : private Eegeo::NonCopyable
            {
            private:
                IThreeSixtyInteractionView& m_view;
                IThreeSixtyInteractionViewModel& m_viewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;


                Eegeo::Helpers::TCallback1<ThreeSixtyInteractionController,std::string&> m_viewModelOpenedCallback;
                Eegeo::Helpers::TCallback0<ThreeSixtyInteractionController> m_viewModelClosedCallback;
                Eegeo::Helpers::TCallback0<ThreeSixtyInteractionController> m_viewClosedCallback;
                Eegeo::Helpers::TCallback1<ThreeSixtyInteractionController,const ThreeSixtyInteraction::ThreeSixtyInteractionMessage&> m_showThreeSixtyInteractionCallback;


                void OnOpenViewModel(std::string& url);
                void OnCloseViewModel();
                void OnCloseTapped();
                void OnShowThreeSixtyInteraction(const ThreeSixtyInteraction::ThreeSixtyInteractionMessage& message);

                
            public:
                ThreeSixtyInteractionController(IThreeSixtyInteractionView& view,
                                                IThreeSixtyInteractionViewModel& viewModel,
                                                ExampleAppMessaging::TMessageBus& messageBus);

                ~ThreeSixtyInteractionController();
            };
        }
    }
}
