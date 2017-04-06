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
                int routeStepID = 0;
                
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
                            if (routeCode == "InternalError" || routeCode == "Error")
                            {
                                responseCode = "Error";
                            }
                            if(json.HasMember("routes") && routeCode != "InternalError")
                            {
                                const rapidjson::Value& innerRouteJsonList = json["routes"];
                                if (innerRouteJsonList.IsNull())
                                {
                                    continue;
                                }
                                
                                size_t numOfInnerEntries = innerRouteJsonList.Size();

                                
                                for(int j = 0; (j < numOfInnerEntries && j< 1); ++j)
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
                                    
                                    std::vector<LegRouteModel> innerRouteLegsVector;
                                    
                                    if(innerRouteJson.HasMember("legs"))
                                    {
                                        const rapidjson::Value& innerRouteLegsValue = innerRouteJson["legs"];
                                        if (innerRouteLegsValue.IsNull())
                                        {
                                            continue;
                                        }
                                        size_t numOfLegs = innerRouteLegsValue.Size();
                                        for(int a = 0; a < numOfLegs; ++a)
                                        {
                                            const rapidjson::Value& legValue = innerRouteLegsValue[a];
                                            
                                            const float legDistance = legValue["distance"].GetDouble();
                                            const float legDuration = legValue["duration"].GetDouble();
                                            const std::string legSummary = legValue["summary"].GetString();
                                            
                                            const rapidjson::Value& stepsValueArray = legValue["steps"];
                                            
                                            std::vector<StepRouteModel> stepVector;
                                            const size_t numOfSteps = stepsValueArray.Size();
                                            
                                            for(int b = 0; b < numOfSteps; ++b)
                                            {
                                                const rapidjson::Value& stepValue = stepsValueArray[b];
                                                
                                                const float setepDistance = stepValue["distance"].GetDouble();
                                                const float setepDuration = stepValue["duration"].GetDouble();
                                                
                                                const std::string stepMode = stepValue["mode"].GetString();
                                                
                                                
                                                const rapidjson::Value& maneuverValue = stepValue["maneuver"];
                                                
                                                const int maneuverBearingAfter = maneuverValue["bearing_after"].GetInt();
                                                const int maneuverBearingBefore = maneuverValue["bearing_before"].GetInt();
                                                const std::string maneuverType = maneuverValue["type"].GetString();
                                                
                                                const rapidjson::Value& maneuverLocationValue = maneuverValue["location"];
                                                
                                                const double maneuverlongitude = maneuverLocationValue[0].GetDouble();
                                                const double maneuverLat = maneuverLocationValue[1].GetDouble();
                                                const Eegeo::Space::LatLong maneuverLocation = Eegeo::Space::LatLong::FromDegrees(maneuverLat,maneuverlongitude);

                                                std::string menuModifer = "";
                                                if (maneuverValue.HasMember("modifier"))
                                                {
                                                    menuModifer = maneuverValue["modifier"].GetString();
                                                }
                                                
                                                std::string stepName = "";
                                                std::string stepBuildingID = "";
                                                bool stepInInterior = false;
                                                int buildingLevel = 0;
                                                std::string buildingLevelString = "";
                                                std::string stepTypeString = "";


                                                if (stepValue.HasMember("name"))
                                                {
                                                    const rapidjson::Value& nameValue = stepValue["name"];
                                                    stepName = nameValue.GetString();
                                                    
                                                    if (stepName.find("bid:") != std::string::npos)
                                                    {
                                                        stepBuildingID = stepName.substr(stepName.find("bid:") + 4);
                                                        stepBuildingID = stepBuildingID.substr(0,stepBuildingID.size()-1);//
                                                        if(stepBuildingID == "c857d08d-7de1-4447-9ff8-6747649a00e0")
                                                        {
                                                            stepBuildingID = "70f9b00f-8c4f-4570-9a23-62bd80a76f8a";
                                                        }
                                                        else
                                                        {
                                                            stepBuildingID = "westport_house";
                                                        }
                                                        stepInInterior = true;
                                                    }
                                                    
                                                    if (stepName.find("level:") != std::string::npos)
                                                    {
                                                        buildingLevelString = stepName.substr(stepName.find("level:") + 6);
                                                        if(buildingLevelString.find("}{") != std::string::npos)
                                                        {
                                                            buildingLevelString = buildingLevelString.substr(0,buildingLevelString.find("}{"));
                                                            if (buildingLevelString != "multiple")
                                                            {
                                                                buildingLevel = std::stoi(buildingLevelString);
                                                            }
                                                            
                                                        }
                                                    }
                                                    
                                                    if (stepName.find("type:") != std::string::npos)
                                                    {
                                                        stepTypeString = stepName.substr(stepName.find("type:") + 5);
                                                        if(stepTypeString.find("}{") != std::string::npos)
                                                        {
                                                            stepTypeString = stepTypeString.substr(0,stepTypeString.find("}{"));
                                                            if(stepTypeString == "pathway")
                                                            {
                                                                //wayPointype = ExampleApp::PathDrawing::WayPointType::Pathway;
                                                            }
                                                            else if (stepTypeString == "entrance")
                                                            {
                                                               // wayPointype = ExampleApp::PathDrawing::WayPointType::Entrance;
                                                                
                                                            }
                                                        }
                                                    }

                                                    
                                                    if (stepInInterior)
                                                    {
                                                        stepTypeString[0] = toupper(stepTypeString[0]);
                                                        stepName =   stepTypeString + " to Floor " + std::to_string(buildingLevel);
                                                    }
                                                }
                                                const ManeuverRouteModel maneuverModelObject(maneuverBearingAfter,maneuverBearingBefore,maneuverType,maneuverLocation,menuModifer);
                                                const StepRouteModel stepModelObject(routeStepID,maneuverModelObject,setepDistance,setepDuration,stepMode,stepName,stepBuildingID,stepInInterior,buildingLevel,stepTypeString);
                                                
                                                stepVector.push_back(stepModelObject);
                                                routeStepID++;

                                                
                                            }
                                            
                                            const LegRouteModel legModelObject(legDistance,legDuration,stepVector,legSummary);
                                            innerRouteLegsVector.push_back(legModelObject);

                                        
                                        
                                        }

                               

                                    }
                                    
                                    DirectionRouteGeometryModel geometryModel(geometryResponseType,coordinatesLatLongVector);
                                    DirectionInnerRouteModel innerRouteModel(innerRouteDuration,innerRouteDistance,geometryModel,innerRouteLegsVector);
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
                                            buildingID = buildingID.substr(0,buildingID.size()-1);//
                                            if(buildingID == "c857d08d-7de1-4447-9ff8-6747649a00e0")
                                            {
                                                buildingID = "70f9b00f-8c4f-4570-9a23-62bd80a76f8a";
                                            }
                                            else
                                            {
                                                buildingID = "westport_house";
                                            }
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
                                            wayPointName =  "Waypoint: " + wayPointTypeString + " at level " + std::to_string(buildingLevel);
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
                                    ExampleApp::PathDrawing::WayPointModel wayPointModel(wayPointsID,wayPointype,latLongStart,wayPointName,buildingID,buildingLevel,inInterior,j);
                                    wayPointsVector.push_back(wayPointModel);
                                    wayPointsID++;
                                    
                                }//end for wayPoints
                            } // end if wayPoint not exist
                            
                            DirectionRouteModel directionRouteModel(routeCode,routeType,wayPointsVector,innerRoutesVector);
                            routes.push_back(directionRouteModel);
                            
                        }// End for outer Routes array
                    } // end if outer route array not exist

                }
                if (responseCode == "Error") {
                    routes.clear();
                }
                return DirectionResultModel(responseCode,responseType,routes);

            }
        }
    }
}
