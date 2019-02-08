// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include <string>
#include <sqlite3.h>
#include "Types.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace Sqlite
        {
            class SqliteDbConnection : private Eegeo::NonCopyable
            {
            private:
                sqlite3 *m_pDbConnection;
                bool m_isDbOpened;
                
            public:
                SqliteDbConnection();

                ~SqliteDbConnection();
                
                bool IsDbOpened() { return m_isDbOpened; }
                
                bool Open(const std::string filePathName);
                
                sqlite3* GetDb() const { return m_pDbConnection; };
            };
        }
    }
}
