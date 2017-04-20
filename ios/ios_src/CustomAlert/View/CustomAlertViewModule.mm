// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CustomAlertView.h"
#include "CustomAlertViewModule.h"
#include "CustomAlertController.h"
#include "CustomAlertViewInterop.h"
#include "ScreenProperties.h"

namespace ExampleApp
{
    namespace CustomAlert
    {
        namespace View
        {
  
            CustomAlertViewModule::CustomAlertViewModule(ICustomAlertViewModel& viewModel,
                                  const Eegeo::Rendering::ScreenProperties& screenProperties,
                                  ExampleAppMessaging::TMessageBus& messageBus)
            {
                
                m_pView = [[CustomAlertView alloc] initWithDimensions:screenProperties.GetScreenWidth() :screenProperties.GetScreenHeight() :screenProperties.GetPixelScale()];
                m_pController = new CustomAlertController(viewModel, *[m_pView getInterop], messageBus);
            }

            CustomAlertViewModule::~CustomAlertViewModule()
            {
                delete m_pController;
                [m_pView release];
            }


            CustomAlertView& CustomAlertViewModule::GetCustomAlertView() const
            {
                return *m_pView;
            }
            
            CustomAlertController& CustomAlertViewModule::GetCustomAlertController() const
            {
                return *m_pController;
            }
        }
    }
}
