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
                
                if (sqlite3_open(filePathName.c_str(), &m_pDbConnection) != SQLITE_OK) {
                    return true;
                } else {
                    m_isDbOpened = true;
                    return true;
                }
            }
        }
    }
}
