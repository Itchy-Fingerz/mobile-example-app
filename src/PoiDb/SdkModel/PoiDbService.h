// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include <string>

#include "IPoiDbService.h"
#include "Types.h"
#include "Sqlite.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            class PoiDbService: public IPoiDbService, private Eegeo::NonCopyable
            {
            private:
//                Sqlite::SqliteDbConnection& m_sqliteDbConnection;
                Sqlite::SqliteTable& m_sqliteDbTable;
                Sqlite::SqliteQueryBuilder& m_sqliteQueryBuilder;
                
            public:
                PoiDbService(Sqlite::SqliteDbConnection* pSqliteDbConnection, Sqlite::SqliteTable* pSqliteDbTable, Sqlite::SqliteQueryBuilder* pSqliteQueryBuilder);

                ~PoiDbService();
                
                virtual void fetchAllRecords(const Search::SdkModel::SearchQuery& query,std::vector<Search::SdkModel::SearchResultModel>& outPutResults);
            };
        }
    }
}
