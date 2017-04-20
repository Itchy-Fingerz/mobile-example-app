// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Rendering.h"
#include "CustomAlertView.h"
#include "CustomAlert.h"
#include "ICustomAlertViewModule.h"
#include "BidirectionalBus.h"


namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace View
        {
            class CustomAlertViewModule: public ICustomAlertViewModule, private Eegeo::NonCopyable
            {
            private:
                CustomAlertView* m_pView;
                CustomAlertController* m_pController;


            public:
                CustomAlertViewModule(ICustomAlertViewModel& viewModel,
                                      const Eegeo::Rendering::ScreenProperties& screenProperties,
                                      ExampleAppMessaging::TMessageBus& messageBus);

                ~CustomAlertViewModule();
                
                CustomAlertView& GetCustomAlertView() const;
                CustomAlertController& GetCustomAlertController() const;

            };
        }
    }
}
