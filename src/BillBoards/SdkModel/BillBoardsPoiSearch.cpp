// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardsPoiSearch.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            BillBoardsPoiSearch::BillBoardsPoiSearch(ExampleApp::SearchMenu::View::SearchMenuController& searchMenuController
                                                         ,ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel)
            : m_appModeChangedCallback(this, &BillBoardsPoiSearch::OnApplicationModeChange)
            , m_appModeModel(appModeModel)
            , m_searchMenuController(searchMenuController)
            {
                m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);                
            }
            
            BillBoardsPoiSearch::~BillBoardsPoiSearch()
            {
                m_appModeModel.UnregisterAppModeChangedCallback(m_appModeChangedCallback);
            }
            
            void BillBoardsPoiSearch::OnApplicationModeChange()
            {
                if (m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
                {
                    m_searchMenuController.OnSearch("advertisements");
                }
                else if (m_appModeModel.GetAppMode() == AppModes::SdkModel::WorldMode)
                {
                    m_searchMenuController.OnSearchCleared();
                }
            }

            
        }
    }
}