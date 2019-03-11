// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include <string>
#include <map>
#include <vector>
#include "Types.h"
#include "WorkItem.h"
#include "PoiDb.h"
#include "Sqlite.h"
#include "SearchResultModel.h"
#include "SqliteTableQuery.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            class PoiDbInsertionTask: public Eegeo::Concurrency::Tasks::WorkItem
            {
            private:
                std::vector<Search::SdkModel::SearchResultModel> m_results;
                Sqlite::SqliteQueryBuilder& m_sqliteQueryBuilder;
                Sqlite::SqliteTable& m_table;
                
            public:
                
                PoiDbInsertionTask(const std::vector<Search::SdkModel::SearchResultModel>& results, Sqlite::SqliteQueryBuilder* pSqliteQueryBuilder, Sqlite::SqliteTable* pTable);
                
                ~PoiDbInsertionTask();
                
                void DoWork();
                void DoFinalizeOnMainThread();
            };
        }
    }
}
