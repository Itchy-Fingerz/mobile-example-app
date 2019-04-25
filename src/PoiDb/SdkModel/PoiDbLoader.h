// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include <string>
#include <map>
#include <vector>
#include "PoiDb.h"
#include "IPoiDbLoader.h"
#include "Types.h"
#include "ICallback.h"
#include "IEegeoPoiSetSearchService.h"
#include "Sqlite.h"
#include "IWorkPool.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            class PoiDbLoader: public IPoiDbLoader, private Eegeo::NonCopyable
            {
            private:
                const std::string m_dbFilePath;
                Sqlite::SqliteDbConnection* m_pSqliteConnection;
                Sqlite::SqliteTable* m_pTable;
                Sqlite::SqliteTable* m_pVenueLabelTable;
                Sqlite::SqliteQueryBuilder* m_pQueryBuilder;
                Eegeo::Helpers::CallbackCollection1<IPoiDbService*> m_serviceStartedCallbacks;
                ExampleApp::Search::EegeoPoisSetService::SdkModel::IEegeoPoiSetSearchService& m_searchService;
                Eegeo::Concurrency::Tasks::IWorkPool& m_workPool;
                
                Eegeo::Helpers::TCallback3<PoiDbLoader,
                const bool&,
                const bool&,
                const std::vector<Search::SdkModel::SearchResultModel>&> m_onResultsReceivedCallback;
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                
            public:
                
                PoiDbLoader(const std::string dbFilePath,
                            ExampleApp::Search::EegeoPoisSetService::SdkModel::IEegeoPoiSetSearchService &searchService,
                            const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,                            Eegeo::Concurrency::Tasks::IWorkPool& workPool);
                
                ~PoiDbLoader();
                
                virtual void CreateDbConnection();
                
                virtual void ResultsReceived(const bool& didSucceed, const bool& isVenueLabel, const std::vector<Search::SdkModel::SearchResultModel>& results);
                
                virtual void InsertOnDbServiceStartedCallback(Eegeo::Helpers::ICallback1<IPoiDbService*>& callback);
                
                virtual void RemoveOnPerformedQueryCallback(Eegeo::Helpers::ICallback1<IPoiDbService*>& callback);
            };
        }
    }
}