// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ARModeMenuOption.h"

#include "IUtils.h"

namespace ExampleApp
{
    namespace ARMode
    {
        namespace View
        {
            ARModeMenuOption::ARModeMenuOption(ExampleApp::Utils::IUtils &utils)
            : m_utils(utils)
            {

            }

            ARModeMenuOption::~ARModeMenuOption()
            {

            }

            void ARModeMenuOption::Select()
            {
                m_utils.OpenARApplication();
            }
        }
    }
}
