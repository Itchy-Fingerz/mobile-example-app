// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "BillBoardsController.h"
#include "BillBoardsRepository.h"
#include "LatLongAltitude.h"
#include "SearchServiceBase.h"
#include "document.h"

#define BOX_WIDTH 12.5
#define BOX_HEIGHT 8.3333

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace SdkModel
        {
            
            BillBoardsController::BillBoardsController(ExampleApp::BillBoards::SdkModel::BillBoardsRepository& billBoardRepository, BillBoards::View::BillBoardService& billBoardServices, ExampleApp::VideoAssetReader::VideoAssetReaderService& videoAssetService, Search::SdkModel::ISearchService& searchService)
            : m_billBoardrepository(billBoardRepository)
            , m_pBillBoardService(billBoardServices)
            , m_videoAssetReaderService(videoAssetService)
            , m_billBoardAddedCallback(this, &BillBoardsController::OnBillBoardAdded)
            , m_billBoardRemoveCallback(this, &BillBoardsController::OnBillBoardAdded)
            , m_searchResultsHandler(this, &BillBoardsController::OnSearchResultsLoaded)
            , m_searchService(searchService)
            {
                
                m_billBoardrepository.InsertItemAddedCallback(m_billBoardAddedCallback);
                m_billBoardrepository.InsertItemRemovedCallback(m_billBoardRemoveCallback);
                m_pBillBoardService.SetVideoService(m_videoAssetReaderService);
                
                m_searchService.InsertOnReceivedQueryResultsCallback(m_searchResultsHandler);

            }
            
            BillBoardsController::~BillBoardsController()
            {
                m_billBoardrepository.RemoveItemAddedCallback(m_billBoardAddedCallback);
                m_billBoardrepository.RemoveItemRemovedCallback(m_billBoardRemoveCallback);
            }
            
            void BillBoardsController::OnBillBoardAdded(ExampleApp::BillBoards::SdkModel::BillBoardModel*&)
            {
            }
            
            void BillBoardsController::OnBillBoardRemoved(ExampleApp::BillBoards::SdkModel::BillBoardModel*&)
            {
            }
            
            void BillBoardsController::OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
            {
                
                rapidjson::Document json;
                std::string descriptionJsonString = "";
                
                for (std::vector<Search::SdkModel::SearchResultModel>::const_iterator resultsItt = results.begin(); resultsItt != results.end(); ++resultsItt)
                {
                    
                    if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("is_billboard_attached"))
                    {
                        
                        if(json["is_billboard_attached"].GetBool())
                        {
                            
                            double originLat;
                            double originLng;
                            
                            BillBoards::View::BillBoardConfig config;
                            config.boxWidth = BOX_WIDTH;
                            config.boxHeight = BOX_HEIGHT;
                            config.poiID = resultsItt->GetIdentifier();
                            
                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("board_id"))
                            {
                                config.billBoardId = json["board_id"].GetInt();
                            }
                            
                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("origin_lat"))
                            {
                                originLat = json["origin_lat"].GetDouble();
                                originLng = json["origin_lng"].GetDouble();
                            }
                            
                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("plane_rotation"))
                            {
                                config.planeRotation = json["plane_rotation"].GetDouble();
                            }
                            
                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("start_hour"))
                            {
                                config.startDisplayingAtHour = json["start_hour"].GetDouble();
                            }
                            
                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("end_hour"))
                            {
                                config.endDisplayingAtHour = json["end_hour"].GetDouble();
                            }
                            
                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("video_url"))
                            {
                                config.videoURL = json["video_url"].GetString();
                            }
                            
                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("is_video"))
                            {
                                config.isVideo = json["is_video"].GetBool();
                            }
                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("floor_index"))
                            {
                                config.floorIndex = json["floor_index"].GetInt();
                            }
                            
                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("altitude"))
                            {
                                config.altitude = json["altitude"].GetDouble();
                            }
                            
                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("texture_file_name"))
                            {
                                config.textureFilename = json["texture_file_name"].GetString();
                            }

                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("unique_tag"))
                            {
                                config.unique_tag = json["unique_tag"].GetString();
                            }
                            for (std::vector<std::string>::const_iterator tagsItt = resultsItt->GetTags().begin(); tagsItt != resultsItt->GetTags().end(); ++tagsItt)
                            {
                                std::string tag = tagsItt->c_str();
                                
                                if(tag == "specialoffer")
                                {
                                    config.isSpecialOffer = true;
                                }
                            }
                            
                            Eegeo::v4 highlightColor = Eegeo::v4(0,0,1,1);
                            std::string highlightColorData = "highlight_color";
                            if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember(highlightColorData.c_str()))
                            {
                                const rapidjson::Value& entity_highlight_color = json[highlightColorData.c_str()];
                                assert(entity_highlight_color.IsArray());
                                
                                if (entity_highlight_color.Size() == 4)
                                {
                                    highlightColor.Set(entity_highlight_color[0].GetDouble()/255.0,
                                                       entity_highlight_color[1].GetDouble()/255.0,
                                                       entity_highlight_color[2].GetDouble()/255.0,
                                                       entity_highlight_color[3].GetDouble()/255.0);
                                }
                            }
                            
                            config.highlightColor = highlightColor;

                            
                            config.originLatLong = std::make_pair(originLat, originLng);
                            config.lineEndTo = std::make_pair(resultsItt->GetLocation().GetLatitudeInDegrees(),resultsItt->GetLocation().GetLongitudeInDegrees());
                            
                            m_pBillBoardService.AddBillboard(config);
                            
                            if(config.isVideo)
                            {
                                AddVideoFrame(config);
                            }
                        }
                    }
                }
                
            }
            
            void BillBoardsController::RefreshBillBoards()
            {
                m_pBillBoardService.RemoveAllRenderables();
                m_pBillBoardService.StopResetVideoService();
                m_pBillBoardService.ResetBillBoardsAfterResume();
                                
            }

            
            void BillBoardsController::CreateMockBillBoards()
            {
//                BillBoards::View::BillBoardConfig config;
//                
//                config.billBoardId = 0;
//                config.textureFilename = "girl";
//                config.originLatLong = std::make_pair(33.944636, -118.411034);
//                config.lineStartFrom = std::make_pair(33.944666, -118.410920);
//                config.lineEndTo = std::make_pair(33.944746, -118.410544);
//                config.altitude = 32.f;
//                config.boxWidth = BOX_WIDTH;
//                config.boxHeight = BOX_HEIGHT;
//                config.planeRotation = -7.0f;
//                config.floorIndex = 2;
//                config.startDisplayingAtHour = 1;   // 24 hours clock 7:00
//                config.endDisplayingAtHour = 23;     //
//                //                m_pBillBoardService->AddBillboard(config);
//                
//                config.billBoardId = 1;
//                config.textureFilename = "test";
//                config.originLatLong = std::make_pair(33.946862, -118.410776);
//                config.lineStartFrom = std::make_pair(33.946724, -118.410759);
//                config.lineEndTo = std::make_pair(33.946190, -118.410288);
//                config.planeRotation = 84.0f;
//                //                m_pBillBoardService->AddBillboard(config);                
//                config.billBoardId = 2;
//                config.floorIndex = 3;
//                config.altitude = 34.f;
//                config.textureFilename = "hardees";
//                config.originLatLong = std::make_pair(33.943890, -118.409679);
//                config.lineStartFrom = std::make_pair(33.943890, -118.409679);
//                config.lineEndTo = std::make_pair(33.943731, -118.410237);
//                config.planeRotation = 174.0f;
//                config.startDisplayingAtHour = 6;   // 24 hours clock 7:00
//                config.endDisplayingAtHour = 23;
//                
//                m_pBillBoardService.AddBillboard(config);
                
//                config.billBoardId = 3;
//                config.floorIndex = 1;
//                config.numberOfFrames = 1;
//                config.altitude = 25.f;
//                config.textureFilename = "sample";
//                config.videoURL = "http://netsolbeta.com/ahmad/TAG.mp4"; //"https://turbooz.com/media/tag.mp4";
//                config.originLatLong = std::make_pair(33.943537, -118.408302);
//                config.lineStartFrom = std::make_pair(33.943530, -118.408376);
//                config.lineEndTo = std::make_pair(33.943333, -118.408784);
//                config.planeRotation = 174.0f;
//                config.isVideo = true;
//                config.startDisplayingAtHour = 1;   // 24 hours clock 7:00
//                config.endDisplayingAtHour = 23;     //
//                m_pBillBoardService.AddBillboard(config);
                
//                config.billBoardId = 4;
//                config.floorIndex = 1;
//                config.altitude = 25.f;
//                config.textureFilename = "video_frame";
//                config.videoURL = "";
//                config.originLatLong = std::make_pair(33.943537, -118.408302);
//                config.lineStartFrom = std::make_pair(33.943518, -118.408407);
//                config.lineEndTo = std::make_pair(33.943290, -118.409007);
//                config.planeRotation = 174.0f;
//                config.isVideo = false;
//                config.isVideoFrame = true;
//                m_pBillBoardService.AddBillboard(config);
                
//                config.billBoardId = 5;
//                config.floorIndex = 2;
//                config.numberOfFrames = 1;
//                config.altitude = 30.f;
//                config.textureFilename = "chaya";
//                config.originLatLong = std::make_pair(33.943697, -118.410977);
//                config.lineStartFrom = std::make_pair(33.943716, -118.410896);
//                config.lineEndTo = std::make_pair(33.943522, -118.410638);
//                config.planeRotation = -18.0f;
//                config.isVideo = false;
//                m_pBillBoardService.AddBillboard(config);

//                config.billBoardId = 4;
//                config.floorIndex = 2;
//                config.numberOfFrames = 1;
//                config.altitude = 30.f;
//                config.textureFilename = "chaya";
//                config.videoURL = "https://turbooz.com/media/tag.mp4";
//                config.originLatLong = std::make_pair(33.943697, -118.410977);
//                config.lineStartFrom = std::make_pair(33.943741, -118.410929);
//                config.lineEndTo = std::make_pair(33.943630, -118.410723);
//                config.planeRotation = -18.0f;
//                config.isVideo = true;
//                m_pBillBoardService.AddBillboard(config);
                
//                config.billBoardId = 6;
//                config.floorIndex = 2;
//                config.altitude = 33.f;
//                config.textureFilename = "tagad";
//                config.videoURL = "http://netsolbeta.com/ahmad/TAG.mp4";//"https://turbooz.com/media/tag.mp4";
//                config.originLatLong = std::make_pair(33.942680, -118.410836);
//                config.lineStartFrom = std::make_pair(33.942687, -118.410762);
//                config.lineEndTo = std::make_pair(33.942656, -118.410554);
//                config.planeRotation = -16.0f;
//                config.isVideo = true;
//                m_pBillBoardService.AddBillboard(config);
//                
//                config.billBoardId = 7;
//                config.floorIndex = 2;
//                config.altitude = 33.f;
//                config.textureFilename = "video_frame";
//                config.videoURL = "";
//                config.originLatLong = std::make_pair(33.942680, -118.410836);
//                config.lineStartFrom = std::make_pair(33.942687, -118.410762);
//                config.lineEndTo = std::make_pair(33.942656, -118.410554);
//                config.planeRotation = -16.0f;
//                config.isVideo = false;
//                config.isVideoFrame = true;
//                m_pBillBoardService.AddBillboard(config);
                
                ///
                
//                config.billBoardId = 8;
//                config.floorIndex = 2;
//                config.altitude = 30.f;
//                config.textureFilename = "chaya";
//                config.originLatLong = std::make_pair(33.945093, -118.411105);
//                config.lineStartFrom = std::make_pair(33.945105, -118.411038);
//                config.lineEndTo = std::make_pair(33.945225, -118.410916);
//                config.planeRotation = -10.0f;
//                config.isVideo = false;
//                m_pBillBoardService.AddBillboard(config);
                
            }
            
            void BillBoardsController::AddVideoFrame(const View::BillBoardConfig& config)
            {
                BillBoards::View::BillBoardConfig tempConfig;
                
                tempConfig.boxWidth = config.boxWidth;
                tempConfig.boxHeight = config.boxHeight;
                tempConfig.billBoardId = (config.billBoardId * 100);
                tempConfig.floorIndex = config.floorIndex;
                tempConfig.altitude = config.altitude;
                tempConfig.textureFilename = "video_frame";
                tempConfig.videoURL = "";
                tempConfig.originLatLong = config.originLatLong;
                tempConfig.lineEndTo = config.lineEndTo;
                tempConfig.planeRotation = config.planeRotation;
                tempConfig.isVideo = false;
                tempConfig.isVideoFrame = true;
                tempConfig.startDisplayingAtHour = config.startDisplayingAtHour;
                tempConfig.endDisplayingAtHour = config.endDisplayingAtHour;                
                tempConfig.poiID = config.poiID;
                tempConfig.highlightColor = config.highlightColor;
                
                m_pBillBoardService.AddBillboard(tempConfig);
                
            }
            
            void BillBoardsController::Update(float dt)
            {
                m_pBillBoardService.Update(dt);
            }

        }
    }
}
