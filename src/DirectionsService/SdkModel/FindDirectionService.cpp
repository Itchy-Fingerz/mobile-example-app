// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "SearchResultModel.h"
#include "FindDirectionService.h"
#include "DirectionQueryResponseReceivedMessage.h"
#include "ISingleOptionAlertBoxDismissedHandler.h"

#include "RouteService.h"
#include "Route.h"
#include "LinearAltitudeBasedRouteThicknessPolicy.h"
#include "RouteStyle.h"
#include "RouteRepository.h"
#include <vector>
#include "AppInteriorCameraWrapper.h"
#include "RenderCamera.h"
#include "InteriorInteractionModel.h"

#include <fstream>
#include "IFileIO.h"
#include "stringbuffer.h"
#include "writer.h"
#include "document.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            void Test(std::string input);
            
            FindDirectionService::FindDirectionService(FindDirectionHttpRequestFactory& findDirectionHttpRequestFactory,Eegeo::Routes::Webservice::JsonRouteParser& resultParser,Eegeo::Routes::RouteService& routeService,Eegeo::Routes::RouteRepository& routeRepository,Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,FindDirectionResultJsonParser& findDirectionResultParser,Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory,ExampleAppMessaging::TMessageBus& messageBus, AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper, Eegeo::Helpers::IFileIO& fileIO)
            : m_pCurrentRequest(NULL)
            , m_findDirectionHttpRequestFactory(findDirectionHttpRequestFactory)
            , m_handleResponseCallback(this,&FindDirectionService::HandleRouteDirectionResponse)
            , m_findDirectionResultParser(findDirectionResultParser)
            , m_resultParser(resultParser)
            , m_failAlertHandler(this, &FindDirectionService::OnFailedToCallRouteResponse)
            , m_alertBoxFactory(alertBoxFactory)
            , m_messageBus(messageBus)
            , m_routeService(routeService)
            , m_routeRepository(routeRepository)
            , m_directionsMenuStateChangedCallback(this, &FindDirectionService::OnDirectionsMenuStateChanged)
            , m_onFindNewDirectionCallback(this, &FindDirectionService::OnFindNewDirection)
            , m_appModeChangedCallback(this, &FindDirectionService::OnAppModeChanged)
            , m_pIsInteriorRoute(false)
            , m_routes (NULL)
            , m_cameraWrapper(cameraWrapper)
            , isRouteDrawn(false)
            , m_fileIO(fileIO)
            {
                m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
                m_messageBus.SubscribeNative(m_onFindNewDirectionCallback);

                m_messageBus.SubscribeUi(m_appModeChangedCallback);
                
                std::fstream stream;
                size_t size;
                
                if(!m_fileIO.OpenFile(stream, size, "SearchResultOnMap/directions_mock_full_response.json"))
                {
                    Eegeo_ASSERT(false, "Failed to load pin sheet definitions file.");
                }
                
                std::string json((std::istreambuf_iterator<char>(stream)),
                                 (std::istreambuf_iterator<char>()));

                responseString = json;
                Test(responseString);

                printf("s");
            }
            
            std::vector<std::string> TokenizeString(std::string mainString , std::string delimiter, bool skipFirstchar)
            {
                std::vector<std::string> resultList;
                std::string mainStrCopy = mainString;
                
                size_t pos = 0;
                std::string token;
                while ((pos = mainStrCopy.find(delimiter)) != std::string::npos)
                {
                    token = mainStrCopy.substr(0, pos);
                    if (skipFirstchar == true)
                    {
                        token.erase(0, 1);
                    }
                    resultList.push_back(token);
                    mainStrCopy.erase(0, pos + delimiter.length());
                }
                if (mainStrCopy !=  "")
                {
                    resultList.push_back(mainStrCopy);
                }
                return resultList;
                
            }

            
            void Test(std::string input)
            {
                rapidjson::Document document;
                
                if (!document.Parse<0>(input.c_str()).HasParseError())
                {
                    
                    if(document.HasMember("routes"))
                    {
                        rapidjson::Value& entries = document["routes"];
                        size_t numEntries = entries.Size();
                        
                        for(int i = 0; i < numEntries; ++i)
                        {
                            std::string routeCode,routeType;
                            
                            rapidjson::Value& json = entries[i];
                            
                            if(json.HasMember("routes") && routeCode != "InternalError")
                            {
                                rapidjson::Value& innerRouteJsonList = json["routes"];
                                if (innerRouteJsonList.IsNull())
                                {
                                    continue;
                                }
                                
                                size_t numOfInnerEntries = innerRouteJsonList.Size();
                                
                                for(int innerRouteNumber = 0; (innerRouteNumber < numOfInnerEntries && innerRouteNumber< 1); ++innerRouteNumber)
                                {
                                    rapidjson::Value& innerRouteJson = innerRouteJsonList[innerRouteNumber];
                                    
                                    std::vector<LegRouteModel> innerRouteLegsVector;
                                    
                                    if(innerRouteJson.HasMember("legs"))
                                    {
                                        rapidjson::Value& innerRouteLegsValue = innerRouteJson["legs"];
                                        if (innerRouteLegsValue.IsNull())
                                        {
                                            continue;
                                        }
                                        size_t numOfLegs = innerRouteLegsValue.Size();
                                        for(int a = 0; a < numOfLegs; ++a)
                                        {
                                            rapidjson::Value& legValue = innerRouteLegsValue[a];
                                            
                                            const std::string legSummary = legValue["summary"].GetString();
                                            
                                            rapidjson::Value& stepsValueArray = legValue["steps"];

                                            //const size_t numOfSteps = stepsValueArray.Size();
                                            
                                            for(int b = 0; b < stepsValueArray.Size(); ++b)
                                            {
                                                const rapidjson::Value& stepValue = stepsValueArray[b];
                                                
                                                
//                                                const std::string stepMode = stepValue["mode"].GetString();
                                                
                                                
//                                                const rapidjson::Value& maneuverValue = stepValue["maneuver"];
                                                
//                                                const std::string maneuverType = maneuverValue["type"].GetString();
                                                
//                                                const rapidjson::Value& maneuverLocationValue = maneuverValue["location"];
                                                
//                                                double maneuverlongitude = maneuverLocationValue[0].GetDouble();
//                                                double maneuverLat = maneuverLocationValue[1].GetDouble();
//                                                if (b == numOfSteps-1)// for last step use geometory last coordinate location
//                                                {//geometry
//                                                    const rapidjson::Value& geometeryValue = stepValue["geometry"];
//                                                    const rapidjson::Value& coordinatesArray = geometeryValue["coordinates"];
//                                                    if (coordinatesArray.Size() >0)
//                                                    {
//                                                        const rapidjson::Value& lastCoordinate = coordinatesArray[coordinatesArray.Size()-1];
//                                                        
//                                                        maneuverlongitude = lastCoordinate[0].GetDouble();
//                                                        maneuverLat = lastCoordinate[1].GetDouble();
//                                                        
//                                                    }
//                                                    
//                                                }
//                                                
                                                std::string stepName = "";
                                                int buildingLevel = 0;
                                                std::string buildingLevelString = "";
                                                std::string stepTypeString = "";
                                                
                                                if (stepValue.HasMember("name"))
                                                {
                                                    const rapidjson::Value& nameValue = stepValue["name"];
                                                    stepName = nameValue.GetString();
                                                    
                                                    std::vector<std::string> stepNameNameVector = TokenizeString(stepName, "}", true);
                                                    if (stepNameNameVector.size() != 0)
                                                    {
                                                        for (std::vector<std::string>::iterator it = stepNameNameVector.begin() ; it != stepNameNameVector.end(); ++it)
                                                        {
                                                            std::vector<std::string> stepNameSubVector = TokenizeString(*it, ":",false);
                                                            if (stepNameSubVector.size() == 2)
                                                            {
                                                                std::string stepSubNameKey = stepNameSubVector[0];
                                                                if (stepSubNameKey == "level")
                                                                {
                                                                    buildingLevelString = stepNameSubVector[1];
                                                                    if (buildingLevelString != "multiple")
                                                                    {
                                                                        buildingLevel = std::stoi(buildingLevelString);
                                                                        if(buildingLevel == 1)
                                                                        {
                                                                            stepsValueArray.Erase(stepsValueArray.Begin() + a);
                                                                            
                                                                            //break;
//                                                                            document.RemoveMember(stepValue);
                                                                            
//                                                                            stepsValueArray.Erase(stepsValueArray.Begin());
                                                                            
                                                                            //stepsValueArray.RemoveMember(stepValue,document.GetAllocator());
                                                                        }
                                                                    }
                                                                    else
                                                                    {
                                                                        
                                                                    }
                                                                }
                                                            }
                                                            
                                                        }
                                                        
                                                    }
                                                    
                                                }
                                            }
                                            
                                        }
                                        
                                    }
                                    
                                }
                            }
                        }
                    }
                }
                
                rapidjson::StringBuffer buffer;
                rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
                document.Accept(writer);
                
                printf("%s", strdup( buffer.GetString() ));
            }
            
            
            FindDirectionService::~FindDirectionService()
            {
                m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);
                m_messageBus.UnsubscribeNative(m_onFindNewDirectionCallback);

                m_messageBus.UnsubscribeUi(m_appModeChangedCallback);


            }
            void FindDirectionService::InsertOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback)
            {
                m_findDirectionqueryResponseReceivedCallbacks.AddCallback(callback);
            }
            
            void FindDirectionService::RemoveOnReceivedQueryResultsCallback(Eegeo::Helpers::ICallback1<const DirectionResultModel& >& callback)
            {
                m_findDirectionqueryResponseReceivedCallbacks.RemoveCallback(callback);
            }
            
            void FindDirectionService::PerformLocationQuerySearch(const Direction::SdkModel::FindDirectionQuery& findDirectionQuery)
            {
                // destroy any existing routes
                m_routeService.DestroyAllRoutes();

                if(m_pCurrentRequest != NULL)
                {
                    m_pCurrentRequest->Cancel();
                }
                m_pIsInteriorRoute = findDirectionQuery.IsInterior();
                if (findDirectionQuery.IsInterior())
                {
                    m_routeThicknessPolicy.SetScaleFactor(0.3f);
                }
                else
                {
                    m_routeThicknessPolicy.SetScaleFactor(1.7f);
                }
//                m_routeThicknessPolicy.SetScaleFactor(0.3f);
                m_pCurrentRequest = m_findDirectionHttpRequestFactory.CreateFindDirectionQuery(findDirectionQuery, m_handleResponseCallback);
                m_pCurrentRequest->Dispatch();

            }
            
            void FindDirectionService::HandleRouteDirectionResponse()
            {
                Eegeo_ASSERT(m_pCurrentRequest != NULL, "Find Direction request must have been performed");
                
                if(m_pCurrentRequest->IsSucceeded())
                {
                    const std::string& response(m_pCurrentRequest->ResponseString());
                    //responseString = response;
                    DirectionResultModel result =  m_findDirectionResultParser.ParseGeoNamesQueryResults(response);
                    m_messageBus.Publish(DirectionResultSection::DirectionQueryResponseReceivedMessage(result));
                    
                    
                    
                    if(result.GetCode() == "Error" || result.GetRoutes().size() == 0)
                    {
                        m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to obtain route.", "No location found matching.", m_failAlertHandler);
                    }
                    else
                    {

                        Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleSegmentedWithDirection, Eegeo::Rendering::LayerIds::InteriorEntities, true, 0.0f);

                        m_resultParser.CreateRouteFromJSON(responseString, m_routeService, routeStyle);
                        
                        isRouteDrawn = true;
                        
                        if(result.GetCode() == "Error" || result.GetRoutes().size() == 0)
                        {
                            m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to obtain route.", "No location found matching.", m_failAlertHandler);
                        }
                        
                    }
                }
                else
                {
                    m_alertBoxFactory.CreateSingleOptionAlertBox("Failed to obtain route.", "No location found matching.", m_failAlertHandler);
                }
                m_pCurrentRequest = NULL;
            }
            
            void FindDirectionService::OnFailedToCallRouteResponse()
            {
                
            }

            void FindDirectionService::ClearRoutes()
            {
                m_routeService.DestroyAllRoutes();
                isRouteDrawn = false;
            }
            
            void FindDirectionService::HideAllRoutes()
            {
                m_routeService.DestroyAllRoutes();
            }
            
            void FindDirectionService::ShowLastRequestRoutes()
            {
                if(isRouteDrawn)
                {
                    Eegeo::Routes::Style::RouteStyle routeStyle(&m_routeThicknessPolicy, Eegeo::Routes::Style::RouteStyle::DebugStyleSegmentedWithDirection, Eegeo::Rendering::LayerIds::InteriorEntities, true, 0.0f);
                
                    m_resultParser.CreateRouteFromJSON(responseString, m_routeService, routeStyle);
                }
            }
            
            void FindDirectionService::OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message)
            {
                if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Inactive)
                {
                    ClearRoutes();
                }
            }
            void FindDirectionService::OnFindNewDirection(const DirectionsMenu::DirectionMenuFindDirectionMessage&)
            {
                ClearRoutes();
            }

            
            void FindDirectionService::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)  // will use for route visibility for different modes otherwise need to remove still facing few issues while regenerating
                                                                                                        //route. Data not exposed.
            {
                if (m_pIsInteriorRoute && message.GetAppMode() == AppModes::SdkModel::InteriorMode)
                {
                    if (m_routes.size() > 0)
                    {
                  
                    }
                  
                }
                else if (m_pIsInteriorRoute)
                {
                    if (m_pIsInteriorRoute)
                    {
                        
                         m_routes = m_routeRepository.GetRoutes();
                    }
                }
            }
            
            void FindDirectionService::Update(float dt)
            {
                float altitude = m_cameraWrapper.GetRenderCamera().GetAltitude();
                altitude = 0;
            }
        }
    }
}
