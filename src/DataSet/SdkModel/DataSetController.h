//
// Created by Najhi Ullah on 08/08/2018.
//

#pragma once

#include "NetIncludes.h"
#include "IDatasetController.h"
#include "DataSet.h"
#include "PersistentSettings.h"
#include "CallbackCollection.h"
#include "Location.h"
#include "InteriorMetaData.h"

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            class DataSetController : public IDataSetController
            {
            private:
                IDataSetCreationQueryFactory& m_dataSetCreationQueryFactory;
                IDataSetInsertQueryFactory& m_dataSetInsertQueryFactory;
                ExampleApp::PersistentSettings::IPersistentSettingsModel& m_persistentSettingsModel;
                Eegeo::Helpers::TCallback0<DataSetController> m_dataSetCreationCallback;
                Eegeo::Helpers::TCallback0<DataSetController> m_dataSetInsertionCallback;
                ExampleApp::Net::SdkModel::INetworkCapabilities& m_networkCapabilities;
                IDataSetCreationQuery* m_pDataSetCreationQuery;
                IDataSetInsertQuery* m_pDataSetInsertQuery;
                Eegeo::Location::ILocationService& m_locationService;
                Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& m_interiorMetaDataRepository;

                void CheckAndDispatchDataSetCreationQuery();
                void HandleDataSetCreationQueryResponse();
                void HandleDataSetInsertionQueryResponse();

                bool m_dataSetCreated;
                bool m_isInFlightQuery;

                float m_minimumDispatchDuration;
                float m_dispatchDuration;
                float m_minimumPositionUpdateDuration;
                float m_positionUpdateDuration;

                std::vector<std::string> m_positionsArray;
            public:
                DataSetController(IDataSetCreationQueryFactory &dataSetCreationQueryFactory,
                                  IDataSetInsertQueryFactory &dataSetInsertQueryFactory,
                                  PersistentSettings::IPersistentSettingsModel &persistentSettings,
                                  Net::SdkModel::INetworkCapabilities &networkCapabilities,
                                  Eegeo::Location::ILocationService &locationService,
                                  Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository &interiorMetaDataRepository);
                ~DataSetController();
                void DumpPositionInArray(double lat, double lng);
                void DispatchPositionsUpdate();
                void Update(float dt);
            };
        }
    }
}
