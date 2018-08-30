//
// Created by Najhi Ullah on 08/08/2018.
//

#pragma once

#include "DataSet.h"
#include "Web.h"
#include "NetIncludes.h"
#include "IDatasetController.h"
#include <string>
#include "PersistentSettings.h"
#include "Location.h"
#include "InteriorMetaData.h"

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            class DataSetModule
            {
            public:
                DataSetModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                              std::string wrldApiKey,
                              Net::SdkModel::INetworkCapabilities& networkCapabilities,
                              PersistentSettings::IPersistentSettingsModel& persistentSettings,
                              Eegeo::Location::ILocationService& locationService,
                              Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository);
                ~DataSetModule();

                IDataSetController& GetController() { return *m_pDataSetController; }

            private:
                IDataSetController *m_pDataSetController;
                DataSetCreationQueryFactory *m_pDataSetCreationQueryFactory;
                DataSetInsertQueryFactory *m_pDataSetInsertQueryFactory;
            };
        }
    }
}

