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
            
            BillBoardsController::BillBoardsController(ExampleApp::BillBoards::SdkModel::BillBoardsRepository& billBoardRepository, BillBoards::View::BillBoardService& billBoardServices, ExampleApp::VideoAssetReader::VideoAssetReaderService& videoAssetService, Search::SdkModel::ISearchService& searchService, Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
            : m_billBoardrepository(billBoardRepository)
            , m_billBoardService(billBoardServices)
            , m_videoAssetReaderService(videoAssetService)
            , m_billBoardAddedCallback(this, &BillBoardsController::OnBillBoardAdded)
            , m_billBoardRemoveCallback(this, &BillBoardsController::OnBillBoardAdded)
            , m_searchResultsHandler(this, &BillBoardsController::OnSearchResultsLoaded)
            , m_searchService(searchService)
            , m_interiorInteractionModel(interiorInteractionModel)
            {
                
                m_billBoardrepository.InsertItemAddedCallback(m_billBoardAddedCallback);
                m_billBoardrepository.InsertItemRemovedCallback(m_billBoardRemoveCallback);
                m_billBoardService.SetVideoService(m_videoAssetReaderService);
                
                m_searchService.InsertOnReceivedQueryResultsCallback(m_searchResultsHandler);

            }
            
            BillBoardsController::~BillBoardsController()
            {
                m_billBoardrepository.RemoveItemAddedCallback(m_billBoardAddedCallback);
                m_billBoardrepository.RemoveItemRemovedCallback(m_billBoardRemoveCallback);
                
                m_searchService.RemoveOnReceivedQueryResultsCallback(m_searchResultsHandler);
            }
            
            void BillBoardsController::OnBillBoardAdded(ExampleApp::BillBoards::SdkModel::BillBoardModel*&)
            {
            }
            
            void BillBoardsController::OnBillBoardRemoved(ExampleApp::BillBoards::SdkModel::BillBoardModel*&)
            {
            }
            
            void BillBoardsController::OnSearchResultsLoaded(const Search::SdkModel::SearchQuery& query, const std::vector<Search::SdkModel::SearchResultModel>& results)
            {
                
                if(query.Query() == "advertisements" || query.Query() == "offers")
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
                                
                                if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("time"))
                                {
                                    config.dayTime = json["time"].GetString();
                                }
                                
                                if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("weather"))
                                {
                                    config.weather = json["weather"].GetString();
                                }
                                if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("season"))
                                {
                                    config.season = json["season"].GetString();
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
                                    
                                    if(tag == "offers")
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
                                
                                m_billBoardService.AddBillboard(config);
                                
                                if(config.isVideo)
                                {
                                    AddVideoFrame(config);
                                }
                            }
                        }
                    }
                    
                    
                    m_billBoardService.SetFloorIndex(m_interiorInteractionModel.GetSelectedFloorIndex());
                    m_billBoardService.CreateBillBoardsFromConfigList();
                    
                }
            }
            
            void BillBoardsController::AddVideoFrame(const View::BillBoardConfig& config)
            {
                BillBoards::View::BillBoardConfig billBoardonfig;
                
                billBoardonfig.boxWidth = config.boxWidth;
                billBoardonfig.boxHeight = config.boxHeight;
                billBoardonfig.billBoardId = (config.billBoardId * 100);
                billBoardonfig.floorIndex = config.floorIndex;
                billBoardonfig.altitude = config.altitude;
                billBoardonfig.textureFilename = "video_frame";
                billBoardonfig.videoURL = "";
                billBoardonfig.originLatLong = config.originLatLong;
                billBoardonfig.lineEndTo = config.lineEndTo;
                billBoardonfig.planeRotation = config.planeRotation;
                billBoardonfig.isVideo = false;
                billBoardonfig.isVideoFrame = true;
                billBoardonfig.dayTime = config.dayTime;
                billBoardonfig.weather = config.weather;
                billBoardonfig.season = config.season;
                billBoardonfig.poiID = config.poiID;
                billBoardonfig.highlightColor = config.highlightColor;
                billBoardonfig.isSpecialOffer = config.isSpecialOffer;
                
                m_billBoardService.AddBillboard(billBoardonfig);
                
            }
            
            void BillBoardsController::Update(float dt)
            {
                m_billBoardService.Update(dt);
            }

        }
    }
}
