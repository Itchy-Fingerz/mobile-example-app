// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ARModeMenuModule.h"

#include "ARModeMenuOption.h"
#include "MenuModel.h"
#include "MenuOptionsModel.h"
#include "MenuViewModel.h"

namespace ExampleApp
{
    namespace ARMode
    {
        namespace SdkModel
        {
            ARModeMenuModule::ARModeMenuModule(Menu::View::IMenuViewModel& menuViewModel, ExampleApp::Utils::IUtils &utils)
            {

                m_pARModeMenuModel = Eegeo_NEW(Menu::View::MenuModel)();
                m_pARModeMenuOptionsModel = Eegeo_NEW(Menu::View::MenuOptionsModel)(*m_pARModeMenuModel);
                m_pARModeMenuOptionsModel->AddItem("AR Mode", "AR Mode", "", "", Eegeo_NEW(View::ARModeMenuOption)(utils));
            }

            ARModeMenuModule::~ARModeMenuModule()
            {
                Eegeo_DELETE m_pARModeMenuOptionsModel;
                Eegeo_DELETE m_pARModeMenuModel;
            }

            Menu::View::IMenuModel& ARModeMenuModule::GetARModeMenuModel() const
            {
                return *m_pARModeMenuModel;
            }
        }
    }
}
