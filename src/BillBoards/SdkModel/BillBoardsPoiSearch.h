// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "BillBoards.h"
#include "IAppModeModel.h"
#include "SearchMenuController.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            class BillBoardsPoiSearch
            {
                
            private:
                
                Eegeo::Helpers::TCallback0<BillBoardsPoiSearch> m_appModeChangedCallback;
                ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel;
                ExampleApp::SearchMenu::View::SearchMenuController& m_searchMenuController;
                
                void OnApplicationModeChange();
                

            public:
                
                BillBoardsPoiSearch(ExampleApp::SearchMenu::View::SearchMenuController& searchMenuController,ExampleApp::AppModes::SdkModel::IAppModeModel& m_appModeModel);
                ~BillBoardsPoiSearch();
            };
        }
    }
}
