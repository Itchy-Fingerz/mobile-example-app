// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>

#include <vector>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {

            struct AnimatedModelsConfig
            {
                const double latitudeInDegrees;
                const double longitudeInDegrees;
                const double altitudeInMetres;
                const std::string filename;
                const std::string indoorMapId;
                const int indoorMapFloorId;
                const std::vector<int> visibleIndoorMapFloorIds;
                const float absoluteHeadingDegrees;
                const float scale;

                AnimatedModelsConfig()
                : latitudeInDegrees(0)
                , longitudeInDegrees(0)
                , altitudeInMetres(0)
                , indoorMapFloorId(0)
                , absoluteHeadingDegrees(0)
                , scale(0)
                {}

                AnimatedModelsConfig(const double lat,
                                     const double lon,
                                     const double alt,
                                     const std::string& file,
                                     const std::string& indoorId,
                                     const int floorId,
                                     const std::vector<int>& visibleFloorIds,
                                     const float heading,
                                     const float modelScale)
                : latitudeInDegrees(lat)
                , longitudeInDegrees(lon)
                , altitudeInMetres(alt)
                , filename(file)
                , indoorMapId(indoorId)
                , indoorMapFloorId(floorId)
                , visibleIndoorMapFloorIds(visibleFloorIds)
                , absoluteHeadingDegrees(heading)
                , scale(modelScale)
                {}
            };
        }
    }
}
