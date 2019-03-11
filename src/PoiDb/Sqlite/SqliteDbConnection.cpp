// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "SqliteDbConnection.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace Sqlite
        {
            SqliteDbConnection::SqliteDbConnection()
            : m_pDbConnection(NULL)
            , m_isDbOpened(false)
            {                
            }
            
            SqliteDbConnection::~SqliteDbConnection()
            {
            }
            
            bool SqliteDbConnection::Open(const std::string filePathName) {
                
                sqlite3_config(SQLITE_CONFIG_SERIALIZED);
                sqlite3_initialize();

                if (sqlite3_open_v2(filePathName.c_str(), &m_pDbConnection, SQLITE_OPEN_READWRITE|SQLITE_OPEN_FULLMUTEX|SQLITE_OPEN_CREATE, NULL) == SQLITE_OK) {
                    m_isDbOpened = true;
                    return true;
                } else {
                    return false;
                }
            }
        }
    }
}
