// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "SqliteTable.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace Sqlite
        {
            SqliteTable::SqliteTable(const std::string& tableName, SqliteDbConnection& dbConnection)
            : m_dbConnection(dbConnection)
            , m_tableName(tableName)
            {
            }
            
            SqliteTable::~SqliteTable()
            {
            }
            
        }
    }
}
