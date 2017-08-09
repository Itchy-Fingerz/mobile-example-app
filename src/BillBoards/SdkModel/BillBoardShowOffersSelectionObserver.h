// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "BidirectionalBus.h"
#include "BillBoardService.h"
#include "ShowOfferHighlightMessage.h"
#include "WayPointOnMapModel.h"
#include "DirectionsMenuStateChangedMessage.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            class BillBoardShowOffersSelectionObserver
            {
            public:
                BillBoardShowOffersSelectionObserver(ExampleAppMessaging::TMessageBus& messageBus
                                                     ,View::BillBoardService& billBoardService,
                                                     PathDrawing::SdkModel::WayPointOnMapModel &wayPointModel);
                ~BillBoardShowOffersSelectionObserver();

            private:                
                Eegeo::Helpers::TCallback1<BillBoardShowOffersSelectionObserver, const ShowOfferHighlightMessage&> m_showOfferSelectionCallback;
                Eegeo::Helpers::TCallback1<BillBoardShowOffersSelectionObserver, const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage&> m_directionsMenuStateChangedCallback;
                PathDrawing::SdkModel::WayPointOnMapModel &m_wayPointModel;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                bool isSpecialOffersModeOn;
                
                void OnShowOfferSelected(const ShowOfferHighlightMessage &message);
                void OnDirectionMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage &message);
            };
        }
    }
}
