// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiDbLoader.h"
#include "PoiDbService.h"
#include "SqliteDbConnection.h"
#include "SqliteQueryBuilder.h"
#include "SqliteTable.h"
#include "SqliteTableQuery.h"
#include "EegeoPoiSetSearchService.h"
#include "SearchResultModel.h"
#include "PoiDbInsertionTask.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {

            PoiDbLoader::PoiDbLoader(const std::string dbFilePath, ExampleApp::Search::EegeoPoisSetService::SdkModel::IEegeoPoiSetSearchService &searchService,
                                     Eegeo::Concurrency::Tasks::IWorkPool& workPool)
            :  m_dbFilePath(dbFilePath)
            , m_pSqliteConnection(NULL)
            , m_pTable(NULL)
            , m_pQueryBuilder(NULL)
            , m_searchService(searchService)
            , m_onResultsReceivedCallback(this, &PoiDbLoader::ResultsReceived)
            , m_workPool(workPool)
            
            {
                m_searchService.InsertOnReceivedQueryResultsForLocalDBCallback(m_onResultsReceivedCallback);
            }

            PoiDbLoader::~PoiDbLoader()
            {
                m_searchService.RemoveOnReceivedQueryResultsForLocalDBCallback(m_onResultsReceivedCallback);
                
                Eegeo_DELETE(m_pSqliteConnection);
                Eegeo_DELETE(m_pTable);
                Eegeo_DELETE(m_pQueryBuilder);
            }
            
            void PoiDbLoader::CreateDbConnection()
            {
                
                m_pSqliteConnection = Eegeo_NEW(PoiDb::Sqlite::SqliteDbConnection)();
                bool isdbOpened = m_pSqliteConnection->Open(m_dbFilePath);
                if(!isdbOpened)
                {
                    return;
                }
                else
                {
                    IPoiDbService* pPoiDbService = NULL;

                    m_pTable = Eegeo_NEW(Sqlite::SqliteTable)("pois", *m_pSqliteConnection);
                    std::vector<std::pair<std::string, std::string>> columnNames = {{"id", "INTEGER PRIMARY KEY"}, {"title","TEXT"}, {"subtitle","TEXT"}, {"latitude_degrees","REAL"}, {"longitude_degrees","REAL"},
                        {"is_interior","INTEGER"}, {"interior_id","TEXT"}, {"floor","INTEGER"}, {"height_terrain","REAL"}, {"tag_icon_key","TEXT"}, {"tags","TEXT"}, {"human_readable_tags","TEXT"}, {"user_data","TEXT"}};
                    m_pQueryBuilder = Eegeo_NEW(PoiDb::Sqlite::SqliteQueryBuilder)(columnNames);
                    pPoiDbService = Eegeo_NEW(PoiDbService)(m_pSqliteConnection, m_pTable, m_pQueryBuilder);
                    m_serviceStartedCallbacks.ExecuteCallbacks(pPoiDbService);                
                }
            }
            
            void PoiDbLoader::ResultsReceived(const bool& didSucceed, const std::vector<Search::SdkModel::SearchResultModel>& results)
            {
                if(!m_pSqliteConnection->IsDbOpened())
                    return;
                
                Sqlite::SqliteTableQuery createTableQuery = m_pQueryBuilder->BuildQuery_CreateTable(*m_pTable);
                createTableQuery.Execute();
                
                if(didSucceed)
                {
                    // Inserting records in seperate thread
                    PoiDbInsertionTask* pTask(Eegeo_NEW(PoiDbInsertionTask)(results, m_pQueryBuilder, m_pTable));
                    m_workPool.QueueWork(pTask);
                }
            }
            
            void PoiDbLoader::InsertOnDbServiceStartedCallback(Eegeo::Helpers::ICallback1<IPoiDbService*>& callback)
            {
                m_serviceStartedCallbacks.AddCallback(callback);
            }

            void PoiDbLoader::RemoveOnPerformedQueryCallback(Eegeo::Helpers::ICallback1<IPoiDbService*>& callback)
            {
                m_serviceStartedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
