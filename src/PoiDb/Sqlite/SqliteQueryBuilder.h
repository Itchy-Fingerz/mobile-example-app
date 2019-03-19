// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <Sqlite.h>
#include <string>
#include <vector>
#include "Types.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace Sqlite
        {
            class SqliteQueryBuilder : private Eegeo::NonCopyable
            {
            private:
                std::vector<std::pair<std::string, std::string>> m_columnNames;
                
            public:
                SqliteQueryBuilder(std::vector<std::pair<std::string, std::string>> columnNames);
                
                ~SqliteQueryBuilder();

                SqliteTableQuery BuildQuery_CreateTable(SqliteTable& table);
                
                SqliteTableQuery BuildQuery_CreateInsertRecord(SqliteTable& table, std::string poi_id, std::string title, std::string sub_title, double lat, double lng, bool isInterior, const std::string interiorId, const int floor, const double height_terrain, const std::string tagIconKey, std::string tags, std::string readeableTags,std::string userData);

                SqliteTableQuery BuildQuery_FetchRecords(SqliteTable& table, std::string queryString, bool isTag, bool isInteriors, int floorIndex);
            };
        }
    }
}
