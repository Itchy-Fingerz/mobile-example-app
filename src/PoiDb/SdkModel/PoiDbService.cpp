// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiDbService.h"
#include "SqliteDbConnection.h"
#include "SqliteTable.h"
#include "SqliteQueryBuilder.h"
#include "SearchResultModel.h"
#include "SearchQuery.h"
#include "SqliteTableQuery.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            PoiDbService::PoiDbService(Sqlite::SqliteDbConnection* pSqliteDbConnection, Sqlite::SqliteTable* pSqliteDbTable, Sqlite::SqliteQueryBuilder* pSqliteQueryBuilder)
            : m_sqliteDbTable(*pSqliteDbTable)
            , m_sqliteQueryBuilder(*pSqliteQueryBuilder)
            {
            }
            
            PoiDbService::~PoiDbService()
            {
            }
            
            void PoiDbService::fetchAllRecords(const Search::SdkModel::SearchQuery& query, std::vector<Search::SdkModel::SearchResultModel>& outPutResults)
            {
                Sqlite::SqliteTableQuery fetchRecordsQuery = m_sqliteQueryBuilder.BuildQuery_FetchRecords(m_sqliteDbTable, query.Query(), true);
                
                fetchRecordsQuery.Execute(outPutResults);                
                return;
            }
        }
    }
}
