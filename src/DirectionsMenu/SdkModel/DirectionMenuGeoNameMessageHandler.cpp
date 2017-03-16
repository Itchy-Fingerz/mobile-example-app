// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionMenuGeoNameMessageHandler.h"
#include "SearchQuery.h"
#include "DirectionMenuGeoNamesResponseReceivedMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            DirectionMenuGeoNameMessageHandler::DirectionMenuGeoNameMessageHandler(ExampleApp::Search::GeoNames::SdkModel::GeoNamesSearchService & geoNamesService, ExampleApp::Search::SdkModel::ISearchService& poiSearchService,ExampleAppMessaging::TMessageBus& messageBus,Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& cameraController)
            
            :m_handleFindDirectionMessageBinding(this, &DirectionMenuGeoNameMessageHandler::OnGetGeoNamesReceivedMessage)
            , m_geoNamesService(geoNamesService)
            , m_poiSearchService(poiSearchService)
            , m_searchQueryResponseCallback(this, &DirectionMenuGeoNameMessageHandler::OnSearchResponseRecieved)
            , m_poiSearchQueryResponseCallback(this, &DirectionMenuGeoNameMessageHandler::OnPoiSearchResponseRecieved)
            , m_isStartLocationActive(true)
            , m_messageBus(messageBus)
            , m_cameraController(cameraController)
            {
                m_messageBus.SubscribeNative(m_handleFindDirectionMessageBinding);
                m_geoNamesService.InsertOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
                m_poiSearchService.InsertOnReceivedQueryResultsCallback(m_poiSearchQueryResponseCallback);
            }
            DirectionMenuGeoNameMessageHandler::~DirectionMenuGeoNameMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handleFindDirectionMessageBinding);
                m_geoNamesService.RemoveOnReceivedQueryResultsCallback(m_searchQueryResponseCallback);
                m_poiSearchService.RemoveOnReceivedQueryResultsCallback(m_poiSearchQueryResponseCallback);
                
                
            }
            void DirectionMenuGeoNameMessageHandler::OnGetGeoNamesReceivedMessage(const DirectionsMenu::DirectionMenuGetGeoNamesMessage& message)
            {                
                bool isTag = false;
                //Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude(0.0f,0.0f,0.0f);
                Eegeo::Space::LatLongAltitude location = Eegeo::Space::LatLongAltitude::FromECEF(m_cameraController.GetEcefInterestPoint());
                float radius = 2000.0f;
                m_isStartLocationActive = message.IsStartLocation();
                Search::SdkModel::SearchQuery searchQuery(message.SearchQuery(), isTag, false, location, radius);
                m_geoNamesService.PerformLocationQuerySearch(searchQuery);
                Search::SdkModel::SearchQuery poi_searchQuery(message.SearchQuery(),isTag,true,location,radius);
                m_poiSearchService.PerformLocationQuerySearch(searchQuery);
                
            }

            void DirectionMenuGeoNameMessageHandler::OnSearchResponseRecieved(const Search::SdkModel::SearchQuery& query,
                                                                 const std::vector<Search::SdkModel::SearchResultModel>& results)
            {
                Eegeo_TTY("Response Received");
                
                m_messageBus.Publish(DirectionsMenu::DirectionMenuGeoNamesResponseReceivedMessage(results,m_isStartLocationActive));
                
            }
            
            
            void DirectionMenuGeoNameMessageHandler::OnPoiSearchResponseRecieved(const Search::SdkModel::SearchQuery& query,
                                                                              const std::vector<Search::SdkModel::SearchResultModel>& results)
            {
                Eegeo_TTY("Response Received");
                
                m_messageBus.Publish(DirectionsMenu::DirectionMenuPoiSearchResponseReceivedMessage(results,m_isStartLocationActive));
                
            }

        }
    }
}
