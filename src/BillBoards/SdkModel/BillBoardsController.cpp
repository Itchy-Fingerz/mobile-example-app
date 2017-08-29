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
                        std::string uniqueTag;
                        bool isSpecialOffer = false;
                        if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("unique_tag"))
                        {
                            uniqueTag = json["unique_tag"].GetString();
                        }
                        
                        for (std::vector<std::string>::const_iterator tagsItt = resultsItt->GetTags().begin(); tagsItt != resultsItt->GetTags().end(); ++tagsItt)
                        {
                            std::string tag = tagsItt->c_str();
                            
                            if(tag == "offers")
                            {
                                isSpecialOffer = true;
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

                        
                        if (!json.Parse<0>(resultsItt->GetJsonData().c_str()).HasParseError() && json.HasMember("is_billboard_attached"))
                        {
                            
                            if(json["is_billboard_attached"].GetBool())
                            {
                                
                                BillBoards::View::BillBoardConfig config;
                                config.boxWidth = BOX_WIDTH;
                                config.boxHeight = BOX_HEIGHT;
                                config.poiID = resultsItt->GetIdentifier();
                                
                                const char* itemKey = "billboards_list";
                                if (json.HasMember(itemKey) && json[itemKey].IsArray())
                                {
                                    const auto& billBoardsModelsMember = json[itemKey];
                                    double originLat;
                                    double originLng;
                                    for (rapidjson::Value::ConstValueIterator it = billBoardsModelsMember.Begin();
                                         it != billBoardsModelsMember.End();
                                         ++it)
                                    {
                                        const auto& item = *it;
                                        
                                        const char* board_idKey = "board_id";
                                        if(!item.HasMember(board_idKey) || !item[board_idKey].IsInt())
                                        {
                                            Eegeo_TTY("no member 'board_id' or is not a string");
                                            break;
                                        }
                                        config.billBoardId = item[board_idKey].GetInt();
                                        
                                        const char* origin_latKey = "origin_lat";
                                        if(!item.HasMember(origin_latKey) || !item[origin_latKey].IsDouble())
                                        {
                                            Eegeo_TTY("no member 'origin_lat' or is not a string");
                                            break;
                                        }
                                        originLat = item[origin_latKey].GetDouble();

                                        const char* origin_lngKey = "origin_lng";
                                        if(!item.HasMember(origin_lngKey) || !item[origin_lngKey].IsDouble())
                                        {
                                            Eegeo_TTY("no member 'origin_lng' or is not a string");
                                            break;
                                        }
                                        originLng = item[origin_lngKey].GetDouble();
                                        
                                        const char* plane_rotationKey = "plane_rotation";
                                        if(!item.HasMember(plane_rotationKey) || !item[plane_rotationKey].IsInt())
                                        {
                                            Eegeo_TTY("no member 'plane_rotationKey' or is not a double");
                                            break;
                                        }
                                        config.planeRotation = item[plane_rotationKey].GetInt();
                                        
                                        const char* timeKey = "time";
                                        if(!item.HasMember(timeKey) || !item[timeKey].IsString())
                                        {
                                            Eegeo_TTY("no member 'time' or is not a string");
                                            break;
                                        }
                                        config.dayTime = item[timeKey].GetString();
                                        
                                        const char* isVideoKey = "is_video";
                                        if(!item.HasMember(isVideoKey) || !item[isVideoKey].IsBool())
                                        {
                                            Eegeo_TTY("no member 'is_video' or is not a Bool");
                                            break;
                                        }
                                        config.isVideo = item[isVideoKey].GetBool();
                                        
                                        if(config.isVideo)
                                        {
                                            const char* video_urlKey = "video_url";
                                            if(!item.HasMember(video_urlKey) || !item[video_urlKey].IsString())
                                            {
                                                Eegeo_TTY("no member 'video_url' or is not a string");
                                                break;
                                            }
                                            config.videoURL = item[video_urlKey].GetString();
                                        }
                                        
                                        const char* floor_IndexKey = "floor_index";
                                        if(!item.HasMember(floor_IndexKey) || !item[floor_IndexKey].IsInt())
                                        {
                                            Eegeo_TTY("no member 'floor_index' or is not a Int");
                                            break;
                                        }
                                        config.floorIndex = item[floor_IndexKey].GetInt();
                                        
                                        const char* altitudeKey = "altitude";
                                        if(!item.HasMember(altitudeKey) || !item[altitudeKey].IsInt())
                                        {
                                            Eegeo_TTY("no member 'altitude' or is not a Int");
                                            break;
                                        }
                                        config.altitude = item[altitudeKey].GetInt();
                                        
                                        const char* texture_file_Key = "texture_file_name";
                                        if(!item.HasMember(texture_file_Key) || !item[texture_file_Key].IsString())
                                        {
                                            Eegeo_TTY("no member 'texture_file_name' or is not a String");
                                            break;
                                        }
                                        config.textureFilename = item[texture_file_Key].GetString();
                                        
                                        config.originLatLong = std::make_pair(originLat, originLng);
                                        config.lineEndTo = std::make_pair(resultsItt->GetLocation().GetLatitudeInDegrees(),resultsItt->GetLocation().GetLongitudeInDegrees());
                                        config.highlightColor = highlightColor;
                                        config.unique_tag = uniqueTag;
                                        config.isSpecialOffer = isSpecialOffer;
                                        m_billBoardService.AddBillboard(config);
                                        
                                        if(config.isVideo)
                                        {
                                            AddVideoFrame(config);
                                        }
                                    }
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
