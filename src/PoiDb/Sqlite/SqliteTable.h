// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include <string>
#include "Sqlite.h"
#include "Types.h"


namespace ExampleApp
{
    namespace PoiDb
    {
        namespace Sqlite
        {
            class SqliteTable : private Eegeo::NonCopyable
            {
            private:
                SqliteDbConnection& m_dbConnection;
                std::string m_tableName;
                
            public:
                SqliteTable(const std::string& tableName, SqliteDbConnection& dbConnection);
                
                ~SqliteTable();
                
                std::string GetTableName() const { return m_tableName; }
                
                SqliteDbConnection& GetDbConnection() const { return m_dbConnection; }
                
            };
        }
    }
}
