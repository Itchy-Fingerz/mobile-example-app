// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "FindDirectionQueryPerformer.h"
#include "DirectionMenuGetGeoNamesMessage.h"
#include "GeoNamesSearchService.h"
#include "GpsGlobeCameraController.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            class DirectionMenuGeoNameMessageHandler : private Eegeo::NonCopyable
            {
            private:
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                ExampleApp::Search::GeoNames::SdkModel::GeoNamesSearchService & m_geoNamesService;
                ExampleApp::Search::SdkModel::ISearchService& m_poiSearchService;
                
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_cameraController;
                
                Eegeo::Helpers::TCallback1<DirectionMenuGeoNameMessageHandler, const DirectionsMenu::DirectionMenuGetGeoNamesMessage&> m_handleFindDirectionMessageBinding;
                
                Eegeo::Helpers::TCallback2<DirectionMenuGeoNameMessageHandler,
                const Search::SdkModel::SearchQuery&,
                const std::vector<Search::SdkModel::SearchResultModel>&> m_searchQueryResponseCallback;
                
                
                Eegeo::Helpers::TCallback2<DirectionMenuGeoNameMessageHandler,
                const Search::SdkModel::SearchQuery&,
                const std::vector<Search::SdkModel::SearchResultModel>&> m_poiSearchQueryResponseCallback;
                
                bool m_isStartLocationActive;
                
                void OnGetGeoNamesReceivedMessage(const DirectionsMenu::DirectionMenuGetGeoNamesMessage& message);
                
                void OnSearchResponseRecieved(const Search::SdkModel::SearchQuery& query,
                                              const std::vector<Search::SdkModel::SearchResultModel>& results);
                
                void OnPoiSearchResponseRecieved(const Search::SdkModel::SearchQuery& query,
                                              const std::vector<Search::SdkModel::SearchResultModel>& results);

                
            public:
                
                DirectionMenuGeoNameMessageHandler(ExampleApp::Search::GeoNames::SdkModel::GeoNamesSearchService & geoNamesService,ExampleApp::Search::SdkModel::ISearchService& poiSearchService, ExampleAppMessaging::TMessageBus& messageBus,Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController);
                ~DirectionMenuGeoNameMessageHandler();
                
            };
        }
    }
}
