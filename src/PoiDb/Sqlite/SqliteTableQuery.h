// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Sqlite.h"
#include <string>
#include "Types.h"


namespace ExampleApp
{
    namespace PoiDb
    {
        namespace Sqlite
        {
            class SqliteTableQuery
            {
            private:
                SqliteDbConnection& m_dbConnection;
                std::string m_query;
                
            public:
                SqliteTableQuery(SqliteDbConnection& dbConnection, std::string query);
                
                ~SqliteTableQuery();
                
                bool Execute();
            };
        }
    }
}
