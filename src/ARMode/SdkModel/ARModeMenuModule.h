// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>

#include "IARModeMenuModule.h"
#include "IIdentity.h"
#include "Menu.h"
#include "Types.h"
#include "Utils.h"

namespace ExampleApp
{
    namespace ARMode
    {
        namespace SdkModel
        {
            class ARModeMenuModule: public IARModeMenuModule, private Eegeo::NonCopyable
            {
            private:
                Menu::View::IMenuModel* m_pARModeMenuModel;
                Menu::View::IMenuOptionsModel* m_pARModeMenuOptionsModel;

            public:
                ARModeMenuModule(Menu::View::IMenuViewModel& menuViewModel, Utils::IUtils& utils);

                ~ARModeMenuModule();

                Menu::View::IMenuModel& GetARModeMenuModel() const;
            };
        }
    }
}
