// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "SqliteQueryBuilder.h"
#include "SqliteTableQuery.h"
#include "SqliteDbConnection.h"
#include "SqliteTable.h"
#include <sstream>
#include <iomanip>


namespace ExampleApp
{
    namespace PoiDb
    {
        #define MAXIMUM_RESULTS_LIMIT 230
        
        namespace Sqlite
        {
            std::string replaceSingleQuote( std::string const& original )
            {
                std::string results(
                                    original.size()
                                    + std::count( original.begin(), original.end(), '\''),
                                    '\'' );
                std::string::iterator dest = results.begin();
                for ( std::string::const_iterator current = original.begin();
                     current != original.end();
                     ++ current ) {
                    if ( *current == '\'' ) {
                        ++ dest;
                    }
                    *dest = *current;
                    ++ dest;
                }
                return results;
            }
            SqliteQueryBuilder::SqliteQueryBuilder(std::vector<std::pair<std::string, std::string>> columnNames) :
            m_columnNames(columnNames)
            {
                
            }
            
            SqliteQueryBuilder::~SqliteQueryBuilder()
            {
                
            }
            
            SqliteTableQuery SqliteQueryBuilder::BuildQuery_CreateTable(SqliteTable& table)
            {
                
                std::stringstream query;
                query << "CREATE TABLE IF NOT EXISTS '";
                query << table.GetTableName();
                query << "' (";
                    
                
                for(std::vector<std::pair<std::string, std::string>>::iterator iterator = m_columnNames.begin(); iterator != m_columnNames.end(); iterator++) {
                    
                    if(iterator != m_columnNames.begin())
                    {
                        query << ", ";
                    }
                    query << "'" << (*iterator).first << "' " << (*iterator).second;
                }
                
                query << ");";
                
                printf("%s", query.str().c_str());
                
                PoiDb::Sqlite::SqliteTableQuery tableQuery = PoiDb::Sqlite::SqliteTableQuery(table.GetDbConnection(), query.str());
                return tableQuery;
            }
            
            SqliteTableQuery SqliteQueryBuilder::BuildQuery_CreateInsertRecord(SqliteTable& table, std::string poi_id, std::string title, std::string sub_title, double lat, double lng, bool isInterior, const std::string interiorId, const int floor, const double height_terrain ,const std::string tagIconKey, std::string tags, std::string readeableTags,std::string userData)
            {
                
                std::stringstream query;
                query << "INSERT OR REPLACE INTO '";
                query << table.GetTableName();
                query << "' (";
                
                
                for(std::vector<std::pair<std::string, std::string>>::iterator iterator = m_columnNames.begin(); iterator != m_columnNames.end(); iterator++) {
                    
                    if(iterator != m_columnNames.begin())
                    {
                        query << ", ";
                    }
                    query << "'" << (*iterator).first << "'";
                }
                
                query << ") VALUES (";
                query << "'" << poi_id << "',";
                query << "'" << replaceSingleQuote(title)  << "',";
                query << "'" << replaceSingleQuote(sub_title) << "',";
                query << "'" << std::setprecision(17) << lat << "',";
                query << "'" << std::setprecision(17) << lng << "',";
                query << "'" << isInterior << "',";
                query << "'" << interiorId << "',";
                query << "'" << floor << "',";
                query << "'" << height_terrain << "',";
                query << "'" << tagIconKey << "',";
                query << "'" << tags << "',";
                query << "'" << readeableTags << "',";
                query << "'" << userData << "'";
                query << ");";
                
                printf("%s", query.str().c_str());

                PoiDb::Sqlite::SqliteTableQuery tableQuery = PoiDb::Sqlite::SqliteTableQuery(table.GetDbConnection(), query.str());
                return tableQuery;
                
            }
            
            SqliteTableQuery SqliteQueryBuilder::BuildQuery_FetchRecords(SqliteTable& table, std::string queryString, bool isTag, bool isInteriors, int floorIndex)
            {

//                SELECT * FROM pois WHERE tags LIKE 'general' ORDER BY CASE floor WHEN 7 THEN -1 ELSE 0 END, floor
                
                std::stringstream query;
                query << "SELECT * FROM ";
                query << table.GetTableName();
                
                if (queryString != "")
                {
                    if(isTag)
                    {
                        query << " WHERE tags LIKE '%";
                        query << replaceSingleQuote(queryString);
                        query << "%'";
                        if (isInteriors)
                        {
                            query << " ORDER BY CASE floor WHEN " << floorIndex;
                            query << " THEN -1 ELSE 0 END, floor";
                        }
                        query << " LIMIT 0 , " << MAXIMUM_RESULTS_LIMIT;
                    }
                    else
                    {
                        query << " WHERE title LIKE '%";
                        query << replaceSingleQuote(queryString);
                        query << "%' ";
                        query << " OR subtitle LIKE '%";
                        query << replaceSingleQuote(queryString);
                        query << "%'";
                        if (isInteriors)
                        {
                            query << " ORDER BY CASE floor WHEN " << floorIndex;
                            query << " THEN -1 ELSE 0 END, floor";
                        }
                        query << " LIMIT 0 , "<< MAXIMUM_RESULTS_LIMIT;
                    }
                }
                PoiDb::Sqlite::SqliteTableQuery tableQuery = PoiDb::Sqlite::SqliteTableQuery(table.GetDbConnection(), query.str());
                return tableQuery;
            }
            
            SqliteTableQuery SqliteQueryBuilder::BuildQuery_FetchRecordsForLabels(SqliteTable& table, int floorIndex)
            {
                std::stringstream query;
                query << "SELECT * FROM ";
                query << table.GetTableName();
//                query << " WHERE floor == "<< floorIndex;
                query << " LIMIT 0 , "<< MAXIMUM_RESULTS_LIMIT;
                
                PoiDb::Sqlite::SqliteTableQuery tableQuery = PoiDb::Sqlite::SqliteTableQuery(table.GetDbConnection(), query.str());
                return tableQuery;
            }
        }
    }
}
