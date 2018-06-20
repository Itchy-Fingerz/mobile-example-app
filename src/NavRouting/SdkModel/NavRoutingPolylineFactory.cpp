// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavRoutingPolylineFactory.h"
#include "PolylineShapeBuilder.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingPolylineFactory::NavRoutingPolylineFactory(PolyLineArgs::IShapeService& shapeService,
                                                                 const NavRoutingPolylineConfig& polylineConfig)
            : m_shapeService(shapeService)
            , m_routeThickness(polylineConfig.routeThickness)
            , m_miterLimit(polylineConfig.miterLimit)
            , m_routeElevation(polylineConfig.routeElevation)
            , m_routeElevationMode(polylineConfig.routeElevationMode)
            , m_shouldScaleWithMap(polylineConfig.shouldScaleWithMap)
            {
                
            }
            
            RouteLines NavRoutingPolylineFactory::CreateLinesForRouteDirection(const NavRoutingDirectionModel& directionModel,
                                                                               const Eegeo::v4& color)
            {
                RouteLines routeLines;
                const auto& coordinates = directionModel.GetPath();
                
                routeLines.push_back(CreatePolyline(coordinates,
                                                    color,
                                                    directionModel.GetIsIndoors(),
                                                    directionModel.GetIndoorMapId().Value(),
                                                    directionModel.GetIndoorMapFloorId()));
                
                return routeLines;
            }
            
            RouteLines NavRoutingPolylineFactory::CreateLinesForRouteDirection(const NavRoutingDirectionModel& directionModel,
                                                                               const Eegeo::v4& forwardColor,
                                                                               const Eegeo::v4& backwardColor,
                                                                               int splitIndex,
                                                                               const Eegeo::Space::LatLong& closestPointOnRoute)
            {
                const auto& coordinates = directionModel.GetPath();
                std::size_t coordinatesSize = coordinates.size();
                bool hasReachedEnd = splitIndex == (coordinatesSize-1);
                
                if (hasReachedEnd)
                {
                    return CreateLinesForRouteDirection(directionModel,
                                                        backwardColor);
                }
                else
                {
                    RouteLines routeLines;
                    std::vector<Eegeo::Space::LatLong> backwardPath;
                    std::vector<Eegeo::Space::LatLong> forwardPath;
                    
                    auto forwardPathSize = coordinatesSize - (splitIndex + 1);
                    forwardPath.reserve(forwardPathSize + 1); //Extra space for the split point
                    
                    auto backwardPathSize = coordinatesSize - forwardPathSize;
                    backwardPath.reserve(backwardPathSize + 1); //Extra space for the split point
                    
                    //Forward path starts with the split point
                    forwardPath.emplace_back(closestPointOnRoute);
                    
                    for (int i = 0; i < coordinatesSize; i++)
                    {
                        if(i<=splitIndex)
                        {
                            backwardPath.emplace_back(coordinates[i]);
                        }
                        else
                        {
                            forwardPath.emplace_back(coordinates[i]);
                        }
                    }
                    
                    //Backward path ends with the split point
                    backwardPath.emplace_back(closestPointOnRoute);
                    
                    routeLines.emplace_back(CreatePolyline(backwardPath,
                                                           backwardColor,
                                                           directionModel.GetIsIndoors(),
                                                           directionModel.GetIndoorMapId().Value(),
                                                           directionModel.GetIndoorMapFloorId()));
                    
                    routeLines.emplace_back(CreatePolyline(forwardPath,
                                                           forwardColor,
                                                           directionModel.GetIsIndoors(),
                                                           directionModel.GetIndoorMapId().Value(),
                                                           directionModel.GetIndoorMapFloorId()));
                    
                    return routeLines;
                }
            }
            
            RouteLines NavRoutingPolylineFactory::CreateLinesForFloorTransition(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                                const std::string& indoorMapId,
                                                                                int floorBefore,
                                                                                int floorAfter,
                                                                                const Eegeo::v4& color)
            {
                double verticalLineHeight = 5.0;
                double lineHeight = (floorAfter > floorBefore) ? verticalLineHeight : -verticalLineHeight;
                
                RouteLines routeLines;
                routeLines.push_back(MakeVerticalLine(coordinates, indoorMapId, floorBefore, 0, lineHeight, color));
                routeLines.push_back(MakeVerticalLine(coordinates, indoorMapId, floorAfter, -lineHeight, 0, color));
                return routeLines;
            }
            
            PolyLineArgs::ShapeModel::IdType NavRoutingPolylineFactory::MakeVerticalLine(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                                         const std::string& indoorMapId,
                                                                                         int floor,
                                                                                         double heightStart,
                                                                                         double heightEnd,
                                                                                         const Eegeo::v4& color)
            {
                std::vector<double> perPointElevations;
                perPointElevations.push_back(heightStart);
                perPointElevations.push_back(heightEnd);
                
                return CreatePolyline(coordinates, color, true, indoorMapId, floor, true, perPointElevations);
            }
            
            PolyLineArgs::ShapeModel::IdType NavRoutingPolylineFactory::CreatePolyline(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                                        const Eegeo::v4& color,
                                                                                        bool isIndoors,
                                                                                        const std::string& indoorMapId,
                                                                                        int indoorMapFloorId,
                                                                                        bool hasPerPointElevation,
                                                                                        const std::vector<double>& perPointElevations)
            {
                Eegeo::Shapes::Polylines::PolylineShapeBuilder shapeBuilder;
                shapeBuilder.SetCoordinates(coordinates)
                            .SetFillColor(color)
                            .SetThickness(m_routeThickness)
                            .SetMiterLimit(m_miterLimit)
                            .SetElevation(m_routeElevation)
                            .SetElevationMode(m_routeElevationMode)
                            .SetShouldScaleWithMap(m_shouldScaleWithMap);
                
                if (isIndoors)
                {
                    shapeBuilder.SetIndoorMap(indoorMapId, indoorMapFloorId);
                }
                
                if (hasPerPointElevation)
                {
                    shapeBuilder.SetPerPointElevations(perPointElevations);
                }
                
                return m_shapeService.Create(shapeBuilder.Build());
            }
        }
    }
}
