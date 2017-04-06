// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IMenuOption.h"

#include <string>

#include "BidirectionalBus.h"
#include "Interiors.h"
#include "IOpenableControlViewModel.h"
#include "Types.h"
#include "VectorMath.h"
#include "IMenuReactionModel.h"
#include "SearchResultPoi.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            class SearchResultItemModel: public Menu::View::IMenuOption, private Eegeo::NonCopyable
            {
                std::string m_name;

                Eegeo::dv3 m_searchResultModelLocationEcef;
                
                bool m_isInterior;
                bool m_isDirections;
                int m_wayPointNumber;
                Eegeo::Resources::Interiors::InteriorId m_interiorId;
                int m_floorIndex;
                ExampleApp::PathDrawing::WayPointType::Values m_wayPointType;


                OpenableControl::View::IOpenableControlViewModel& m_searchMenuViewModel;
                SearchResultPoi::View::ISearchResultPoiViewModel& m_searchResultPoiViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                int m_itemIndex;

                const Menu::View::IMenuReactionModel& m_menuReaction;
            public:
                SearchResultItemModel(const std::string& name,
                                      const Eegeo::dv3& searchResultModelLocationEcef,
                                      const bool isInterior,
                                      const bool isDirections,
                                      const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                      const int floorIndex,
                                      OpenableControl::View::IOpenableControlViewModel& searchMenuViewModel,
                                      SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel,
                                      int itemIndex,
                                      ExampleAppMessaging::TMessageBus& messageBus,
                                      const Menu::View::IMenuReactionModel& menuReaction,
                                      int wayPointNumber,
                                      ExampleApp::PathDrawing::WayPointType::Values wayPointType);

                ~SearchResultItemModel();

                void Select();
                
                int GetItemIndex();
                
                Eegeo::dv3 GetLocationEcef();
                bool GetIsInterior();
                std::string GetInteriorID();
                std::string GetName();
                int GetFloorIndex();
                int GetWayPointNumber();
                ExampleApp::PathDrawing::WayPointType::Values GetWayPointType();

            };
        }
    }

}
