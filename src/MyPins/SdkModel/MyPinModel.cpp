// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            /*
                Version 1: Initial version
                Version 2: Added optional ratings image & reviews count data (8/7/15)
             */
            const int MyPinModel::CurrentVersion = 2;
            
            MyPinModel::MyPinModel()
                : m_version(-1)
                , m_modelId(-1)
                , m_latLong(0.0, 0.0)
                , m_heightAboveTerrainMetres(0)
                , m_interior(false)
                , m_buildingId("")
                , m_floor(0)
            {

            }

            MyPinModel::MyPinModel(int version,
                                   int modelId,
                                   const std::string& title,
                                   const std::string& description,
                                   const std::string& ratingsImage,
                                   int reviewCount,
                                   int sdkMapPinIconIndex,
                                   const Eegeo::Space::LatLong& latLong,
                                   float heightAboveTerrainMetres,
                                   bool interior,
                                   const Eegeo::Resources::Interiors::InteriorId& buildingId,
                                   int floor)
            : m_version(version)
            , m_modelId(modelId)
            , m_title(title)
            , m_description(description)
            , m_ratingsImage(ratingsImage)
            , m_reviewCount(reviewCount)
            , m_sdkMapPinIconIndex(sdkMapPinIconIndex)
            , m_latLong(latLong)
            , m_heightAboveTerrainMetres(heightAboveTerrainMetres)
            , m_interior(interior)
            , m_buildingId(buildingId)
            , m_floor(floor)
            {
                
            }
        }
    }
}
