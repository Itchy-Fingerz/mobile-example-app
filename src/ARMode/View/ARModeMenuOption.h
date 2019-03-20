// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"

#include "Utils.h"
#include "Menu.h"
#include "Types.h"

namespace ExampleApp
{
    namespace ARMode
    {
        namespace View
        {
            class ARModeMenuOption : public Menu::View::IMenuOption, private Eegeo::NonCopyable
            {
                ExampleApp::Utils::IUtils &m_utils;

            public:
                ARModeMenuOption(ExampleApp::Utils::IUtils &utils);

                ~ARModeMenuOption();

                void Select();
            };
        }
    }
}
