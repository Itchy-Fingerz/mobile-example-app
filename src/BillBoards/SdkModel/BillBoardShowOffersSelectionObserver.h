// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "BidirectionalBus.h"
#include "BillBoardService.h"
#include "ShowOfferHighlightMessage.h"
#include "WayPointOnMapModel.h"
#include "DirectionsMenuStateChangedMessage.h"
#include "FindDirectionService.h"
#include "IMenuViewModel.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            class BillBoardShowOffersSelectionObserver
            {
            public:
                BillBoardShowOffersSelectionObserver(View::BillBoardService& billBoardService,
                                                     PathDrawing::SdkModel::WayPointOnMapModel &wayPointModel,Direction::SdkModel::FindDirectionService &findDirectionService, Menu::View::IMenuViewModel& directionViewModel,ExampleAppMessaging::TMessageBus& messageBus);
                ~BillBoardShowOffersSelectionObserver();

            private:                
                Eegeo::Helpers::TCallback1<BillBoardShowOffersSelectionObserver, const ShowOfferHighlightMessage&> m_showOfferSelectionCallback;
                Eegeo::Helpers::TCallback1<BillBoardShowOffersSelectionObserver, const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage&> m_directionsMenuStateChangedCallback;
                PathDrawing::SdkModel::WayPointOnMapModel &m_wayPointModel;
                Direction::SdkModel::FindDirectionService &m_findDirectionService;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                bool isSpecialOffersModeOn;
                Menu::View::IMenuViewModel& m_directionViewModel;
                
                void OnShowOfferSelected(const ShowOfferHighlightMessage &message);
                void OnDirectionMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage &message);
            };
        }
    }
}
