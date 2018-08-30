//
// Created by Najhi Ullah on 08/08/2018.
//

#include "DataSetController.h"
#include "IPersistentSettingsModel.h"
#include "IDataSetCreationQueryFactory.h"
#include "IDataSetInsertQueryFactory.h"
#include "INetworkCapabilities.h"
#include "IDataSetCreationQuery.h"
#include "IDataSetInsertQuery.h"
#include "LatLongAltitude.h"
#include "ILocationService.h"
#include "InteriorMetaDataRepository.h"
#include "ApplicationInteriorTrackingInfo.h"
#include "IPSConfigurationParser.h"
#include "DataSetInsertQueryModel.h"

#include <sstream>
#include <vector>

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            DataSetController::DataSetController(IDataSetCreationQueryFactory &dataSetCreationQueryFactory,
                                                 IDataSetInsertQueryFactory &dataSetInsertQueryFactory,
                                                 PersistentSettings::IPersistentSettingsModel &persistentSettings,
                                                 Net::SdkModel::INetworkCapabilities &networkCapabilities,
                                                 Eegeo::Location::ILocationService &locationService,
                                                 Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository &interiorMetaDataRepository)
            : m_dataSetCreationQueryFactory(dataSetCreationQueryFactory)
            , m_dataSetInsertQueryFactory(dataSetInsertQueryFactory)
            , m_persistentSettingsModel(persistentSettings)
            , m_dataSetCreationCallback(this, &DataSetController::HandleDataSetCreationQueryResponse)
            , m_dataSetInsertionCallback(this, &DataSetController::HandleDataSetInsertionQueryResponse)
            , m_dataSetCreated(true)
            , m_networkCapabilities(networkCapabilities)
            , m_isInFlightQuery(false)
            , m_locationService(locationService)
            , m_minimumDispatchDuration(15.0f)
            , m_dispatchDuration(0.0f)
            , m_minimumPositionUpdateDuration(2.0f)
            , m_positionUpdateDuration(0.0f)
            , m_interiorMetaDataRepository(interiorMetaDataRepository)
            , m_pDataSetCreationQuery(NULL)
            , m_pDataSetInsertQuery(NULL)
            {

            }

            DataSetController::~DataSetController()
            {
                if(m_pDataSetCreationQuery != NULL)
                {
                    m_pDataSetCreationQuery->Cancel();
                    m_pDataSetCreationQuery = NULL;
                }
            }

            void DataSetController::CheckAndDispatchDataSetCreationQuery()
            {
                const bool noWifi = m_networkCapabilities.StreamOverWifiOnly() && !m_networkCapabilities.ConnectedToWifi();

                if(noWifi)
                {
                    return;
                }

                bool outValue;
                m_persistentSettingsModel.TryGetValue("dataSetCreated_key", outValue);

                if(!outValue)
                {
                    m_isInFlightQuery = true;
                    m_pDataSetCreationQuery = m_dataSetCreationQueryFactory.CreateDataSetCreationQuery(m_dataSetCreationCallback);
                    m_pDataSetCreationQuery->Dispatch();
                }
            }

            void DataSetController::HandleDataSetCreationQueryResponse()
            {
                if(m_pDataSetCreationQuery->IsSucceeded())
                {
                    m_dataSetCreated = true;
                    m_persistentSettingsModel.SetValue("dataSetCreated_key", m_dataSetCreated);
                }

                m_pDataSetCreationQuery = NULL;

                m_isInFlightQuery = false;
            }

            void DataSetController::DumpPositionInArray(double lat, double lng)
            {
                std::ostringstream lats;
                lats << lat;
                std::string latStr = lats.str();

                std::ostringstream lngs;
                lngs << lng;
                std::string lngStr = lngs.str();

                time_t timeStamp;
                time(&timeStamp);

                std::ostringstream times;
                times << timeStamp;
                std::string timeStampStr = times.str();

                std::string infoStr = "{\"producer_guid\":\"123456789\","
                                      "\"type\":\"user_poi\","
                                      "\"value\":-1,"
                                      "\"userdata\":\"lat=" + latStr + ",lng=" + lngStr + ",ts=" + timeStampStr + "\"}";

                m_positionsArray.push_back(infoStr);
            }

            void DataSetController::DispatchPositionsUpdate()
            {
                const bool noWifi = m_networkCapabilities.StreamOverWifiOnly() && !m_networkCapabilities.ConnectedToWifi();

                if(noWifi)
                {
                    return;
                }

                m_isInFlightQuery = true;

                std::string tempPositions = "";
                for(std::vector<std::string>::iterator it = m_positionsArray.begin() ; it != m_positionsArray.end() ; ++it)
                {
                    tempPositions += *it +",";
                }

                std::string positions = tempPositions.substr(0, tempPositions.size() - 1);

                std::string infoStr = "[" + positions + "]";

                DataSetInsertQueryModel* model = Eegeo_NEW(ExampleApp::DataSet::SdkModel::DataSetInsertQueryModel)(infoStr);
                m_pDataSetInsertQuery = m_dataSetInsertQueryFactory.CreateDataSetInsertQuery(*model, m_dataSetInsertionCallback);
                m_pDataSetInsertQuery->Dispatch();

                Eegeo_DELETE model;
                m_positionsArray.clear();
            }

            void DataSetController::HandleDataSetInsertionQueryResponse()
            {
                if(m_pDataSetInsertQuery->IsSucceeded())
                {
                    Eegeo_TTY("Dataset Updated Successfully");
                }

                m_pDataSetInsertQuery = NULL;

                m_isInFlightQuery = false;
            }

            void DataSetController::Update(float dt)
            {
                if(m_isInFlightQuery)
                {
                    return;
                }

                if(!m_dataSetCreated)
                {
                    CheckAndDispatchDataSetCreationQuery();
                    return;
                }

                bool dispatchPositionsUpdate = false;
                m_dispatchDuration += dt;

                if(m_dispatchDuration >= m_minimumDispatchDuration)
                {
                    dispatchPositionsUpdate = true;
                    m_dispatchDuration = 0;
                }

                typedef std::map<std::string, ApplicationConfig::SdkModel::ApplicationInteriorTrackingInfo> TrackingInfoMap;

                if(m_locationService.IsIndoors())
                {
                    Eegeo::Resources::Interiors::InteriorId interiorId = m_locationService.GetInteriorId();
                    if(interiorId.IsValid())
                    {
                        if(interiorId.IsValid() && interiorId.Value() == "jcgroup_china_suzhou")
                        {
                            Eegeo::Space::LatLong locationServiceLatLng(0,0);
                            if(m_locationService.GetLocation(locationServiceLatLng))
                            {

                                m_positionUpdateDuration += dt;
                                if(m_positionUpdateDuration >= m_minimumPositionUpdateDuration)
                                {
                                    DumpPositionInArray(locationServiceLatLng.GetLatitudeInDegrees(), locationServiceLatLng.GetLongitudeInDegrees());
                                    m_positionUpdateDuration = 0.0f;
                                    Eegeo_TTY("Dataset: Update position");
                                }

                                if(dispatchPositionsUpdate)
                                {
                                    DispatchPositionsUpdate();
                                    Eegeo_TTY("Dataset: Dispatch position");
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}