// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "SqliteTableQuery.h"
#include <sqlite3.h>
#include "SqliteDbConnection.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace Sqlite
        {
            SqliteTableQuery::SqliteTableQuery(SqliteDbConnection& dbConnection, std::string query)
            : m_dbConnection(dbConnection)
            , m_query(query)
            {
            }
            
            SqliteTableQuery::~SqliteTableQuery()
            {
            }
            
            bool SqliteTableQuery::Execute()
            {
                char *err;
        
                if(sqlite3_exec(m_dbConnection.GetDb(), m_query.c_str(), NULL, NULL, &err) != SQLITE_OK)
                {
                    printf("Failed to execute query. \n");
                } else {
                    printf("Query executed successfully. \n");
                    return true;
                }
                return false;
            }
            
        }
    }
}
