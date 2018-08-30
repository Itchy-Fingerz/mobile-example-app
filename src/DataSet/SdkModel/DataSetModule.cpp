//
// Created by Najhi Ullah on 08/08/2018.
//

#include "Types.h"
#include "DataSetModule.h"
#include "DataSetController.h"
#include "DataSetCreationQueryFactory.h"
#include "DataSetInsertQueryFactory.h"

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            const std::string m_apiUrl = "https://wrld-data-service-staging.herokuapp.com/v0.1";

            DataSetModule::DataSetModule(Eegeo::Web::IWebLoadRequestFactory &webRequestFactory,
                                         std::string wrldApiKey,
                                         Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                         PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                         Eegeo::Location::ILocationService& locationService,
                                         Eegeo::Resources::Interiors::MetaData::InteriorMetaDataRepository& interiorMetaDataRepository)
            {
                m_pDataSetCreationQueryFactory = Eegeo_NEW(ExampleApp::DataSet::SdkModel::DataSetCreationQueryFactory)(m_apiUrl, wrldApiKey, webRequestFactory);

                m_pDataSetInsertQueryFactory = Eegeo_NEW(ExampleApp::DataSet::SdkModel::DataSetInsertQueryFactory)(m_apiUrl, wrldApiKey, webRequestFactory);

                m_pDataSetController = Eegeo_NEW(ExampleApp::DataSet::SdkModel::DataSetController)(*m_pDataSetCreationQueryFactory,
                                                                                                   *m_pDataSetInsertQueryFactory,
                                                                                                   persistentSettings,
                                                                                                   networkCapabilities,
                                                                                                   locationService,
                                                                                                   interiorMetaDataRepository);
            }

            DataSetModule::~DataSetModule()
            {
                Eegeo_DELETE m_pDataSetController;
                m_pDataSetController = NULL;

                Eegeo_DELETE m_pDataSetCreationQueryFactory;
                m_pDataSetCreationQueryFactory = NULL;

                Eegeo_DELETE m_pDataSetInsertQueryFactory;
                m_pDataSetInsertQueryFactory = NULL;
            }
        }
    }
}