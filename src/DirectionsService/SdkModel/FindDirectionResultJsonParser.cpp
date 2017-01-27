// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "FindDirectionResultJsonParser.h"
#include "WayPointType.h"
namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            
            FindDirectionResultJsonParser::FindDirectionResultJsonParser()
            {
            
            }
            
            FindDirectionResultJsonParser::~FindDirectionResultJsonParser()
            {
            
            }
            
            DirectionResultModel FindDirectionResultJsonParser::ParseGeoNamesQueryResults(const std::string& serialized)
            {
                rapidjson::Document document;
                std::vector<DirectionRouteModel> routes;
                std::string responseCode = "";
                std::string responseType = "";
                int wayPointsID = 0;
                
                if (!document.Parse<0>(serialized.c_str()).HasParseError())
                {
                    
                    if(document.HasMember("code"))
                    {
                        const rapidjson::Value& code = document["code"];
                        responseCode = code.GetString();
                    }
                    if(document.HasMember("type"))
                    {
                        const rapidjson::Value& code = document["type"];
                        responseType = code.GetString();
                    }
                    

                    if(document.HasMember("routes"))
                    {
                        const rapidjson::Value& entries = document["routes"];
                        size_t numEntries = entries.Size();
                        
                        for(int i = 0; i < numEntries; ++i)
                        {
                            std::string routeCode,routeType;



                            const rapidjson::Value& json = entries[i];
                            if(json.HasMember("code"))
                            {
                                const rapidjson::Value& code = json["code"];
                                routeCode = code.GetString();
                            }
                            if(json.HasMember("type"))
                            {
                                const rapidjson::Value& typeValue = json["type"];
                                routeType = typeValue.GetString();
                            }
                            
                            std::vector<DirectionInnerRouteModel> innerRoutesVector;
                            
                            if(json.HasMember("routes") && routeCode != "InternalError")
                            {
                                const rapidjson::Value& innerRouteJsonList = json["routes"];
                                if (innerRouteJsonList.IsNull())
                                {
                                    continue;
                                }
                                
                                size_t numOfInnerEntries = innerRouteJsonList.Size();

                                
                                for(int j = 0; j < numOfInnerEntries; ++j)
                                {
                                    int innerRouteDuration,innerRouteDistance;
                                    const rapidjson::Value& innerRouteJson = innerRouteJsonList[j];
                                    
                                    if (innerRouteJson.HasMember("duration"))
                                    {
                                        const rapidjson::Value& durationVal = innerRouteJson["duration"];
                                        innerRouteDuration = durationVal.GetDouble();
                                    }
                                    
                                    if (innerRouteJson.HasMember("distance"))
                                    {
                                        const rapidjson::Value& distanceVal = innerRouteJson["distance"];
                                        innerRouteDistance = distanceVal.GetDouble();
                                    }
                                    
                                    std::string geometryResponseType = "";
                                    std::vector<Eegeo::Space::LatLong> coordinatesLatLongVector;
                                    
                                    if (innerRouteJson.HasMember("geometry"))
                                    {
                                        const rapidjson::Value& geometryJson = innerRouteJson["geometry"];
                                        const rapidjson::Value& geometryTypeJson = geometryJson["type"];
                                        geometryResponseType = geometryTypeJson.GetString();
                                        const rapidjson::Value& coordinatesListValue = geometryJson["coordinates"];
                                        size_t numCoordinatesListVal = coordinatesListValue.Size();

                                        for(int k = 0; k < numCoordinatesListVal; ++k)
                                        {
                                            const rapidjson::Value& coordinateJsonValue = coordinatesListValue[k];
                                            Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromDegrees(coordinateJsonValue[1].GetDouble(),
                                                                                                  coordinateJsonValue[0].GetDouble());
                                            coordinatesLatLongVector.push_back(latLong);
                                            
                                        }
                                    }
                                    
                                    DirectionRouteGeometryModel geometryModel(geometryResponseType,coordinatesLatLongVector);
                                    DirectionInnerRouteModel innerRouteModel(innerRouteDuration,innerRouteDistance,geometryModel);
                                    innerRoutesVector.push_back(innerRouteModel);
                                    
                                    
                                }//end for for inner Routes
                                
                            } // End if inner routes array not exisit
                            
                            std::vector<ExampleApp::PathDrawing::WayPointModel> wayPointsVector;
                            
                            if(json.HasMember("waypoints"))
                            {
                                const rapidjson::Value& routeWayPoints = json["waypoints"];
                                if (routeWayPoints.IsNull())
                                {
                                    continue;
                                }
                                size_t numOfWayPoints = routeWayPoints.Size();
                                for(int j = 0; j < numOfWayPoints; ++j)
                                {
                                    std::string wayPointName,wayPointHint;
                                    std::string buildingID = "";
                                    double lat = 0;
                                    double longi = 0;
                                    bool inInterior = false;
                                    int buildingLevel = 0;
                                    std::string buildingLevelString = "";
                                    std::string wayPointTypeString = "";
                                    ExampleApp::PathDrawing::WayPointType::Values wayPointype = ExampleApp::PathDrawing::WayPointType::CheckPoint;
                                    const rapidjson::Value& wayPointJsonValue = routeWayPoints[j];
                                    
                                    if (wayPointJsonValue.HasMember("name"))
                                    {
                                        const rapidjson::Value& nameValue = wayPointJsonValue["name"];
                                        wayPointName = nameValue.GetString();

                                        if (wayPointName.find("bid:") != std::string::npos)
                                        {
                                            buildingID = wayPointName.substr(wayPointName.find("bid:") + 4);
                                            buildingID = "westport_house";//buildingID.substr(0,buildingID.size()-1);
                                            inInterior = true;
                                        }
                                        
                                        if (wayPointName.find("level:") != std::string::npos)
                                        {
                                            buildingLevelString = wayPointName.substr(wayPointName.find("level:") + 6);
                                            if(buildingLevelString.find("}{") != std::string::npos)
                                            {
                                                buildingLevelString = buildingLevelString.substr(0,buildingLevelString.find("}{"));
                                                buildingLevel = std::stoi(buildingLevelString);
                                            }
                                        }
                                        
                                        if (wayPointName.find("type:") != std::string::npos)
                                        {
                                            wayPointTypeString = wayPointName.substr(wayPointName.find("type:") + 5);
                                            if(wayPointTypeString.find("}{") != std::string::npos)
                                            {
                                                wayPointTypeString = wayPointTypeString.substr(0,wayPointTypeString.find("}{"));
                                                if(wayPointTypeString == "pathway")
                                                {
                                                    wayPointype = ExampleApp::PathDrawing::WayPointType::Pathway;
                                                }
                                                else if (wayPointTypeString == "entrance")
                                                {
                                                    wayPointype = ExampleApp::PathDrawing::WayPointType::Entrance;

                                                }
                                            }
                                        }
                                        
                                        if (inInterior)
                                        {
                                            wayPointName =  "Waypoint: " + wayPointTypeString + "at level " + std::to_string(buildingLevel);
                                        }

                                    }
                                    
                                    if (wayPointJsonValue.HasMember("hint"))
                                    {
                                        const rapidjson::Value& hintJsonValue = wayPointJsonValue["hint"];
                                        wayPointHint = hintJsonValue.GetString();
                                    }
                                    
                                    if (wayPointJsonValue.HasMember("location"))
                                    {
                                        const rapidjson::Value& wayPointLocationJson = wayPointJsonValue["location"];
                                        lat = wayPointLocationJson[1].GetDouble();
                                        longi = wayPointLocationJson[0].GetDouble();
                                    }
                                    Eegeo::Space::LatLong latLongStart = Eegeo::Space::LatLong::FromDegrees(lat,longi);
                                    ExampleApp::PathDrawing::WayPointModel wayPointModel(wayPointsID,wayPointype,latLongStart,wayPointName,buildingID,buildingLevel,inInterior);
                                    wayPointsVector.push_back(wayPointModel);
                                    wayPointsID++;
                                    
                                }//end for wayPoints
                            } // end if wayPoint not exist
                            
                            DirectionRouteModel directionRouteModel(routeCode,routeType,wayPointsVector,innerRoutesVector);
                            routes.push_back(directionRouteModel);
                            
                        }// End for outer Routes array
                    } // end if outer route array not exist

                }
                return DirectionResultModel(responseCode,responseType,routes);

            }
        }
    }
}