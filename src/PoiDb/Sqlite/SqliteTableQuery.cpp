// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "SqliteTableQuery.h"
#include "SqliteDbConnection.h"
#include "SearchResultModel.h"
#include "TimeHelpers.h"
#include "SearchVendorNames.h"
#include "SqliteTable.h"
#include <sstream>

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace Sqlite
        {
            enum PoiColumnindices
            {
                poi_id = 0,
                poi_title,
                poi_subtitle,
                poi_latitude_degrees,
                poi_longitude_degrees,
                poi_is_interior,
                poi_interior_id,
                poi_floor,
                poi_height_terrain,
                poi_icon_key,
                poi_tags,
                poi_readable_tags,
                poi_user_data,
                PoiColumnindices_MAX
            };
            
            std::vector<std::string> GetTagsFromString(const std::string tagsStr)
            {
                std::vector<std::string> returnTags;
                unsigned previous_start = -1;
                
                for (unsigned i = 0; i < tagsStr.length(); ++i)
                {
                    if (tagsStr[i] == ',')
                    {
                        returnTags.push_back(tagsStr.substr(previous_start + 1, i - previous_start - 1));
                        previous_start = i;
                    }
                }
                
                if (previous_start != tagsStr.length() - 1)
                {
                    returnTags.push_back(tagsStr.substr(previous_start + 1));
                }
                
                return returnTags;
            }
            
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

            bool SqliteTableQuery::Execute(std::vector<Search::SdkModel::SearchResultModel>& outPutResults)
            {
                sqlite3_stmt *statement = NULL;
                
                if (sqlite3_prepare_v2(m_dbConnection.GetDb(), m_query.c_str(), -1, &statement, NULL) != SQLITE_OK) {
                    printf("[SQLITE] can't query data！\n");
                } else {
                    
                    while (sqlite3_step(statement) == SQLITE_ROW) {
                        
                        char * identifier =  (char *)sqlite3_column_text(statement, poi_id);
                        char * title =  (char *)sqlite3_column_text(statement, poi_title);
                        char * subtitle =  (char *)sqlite3_column_text(statement, poi_subtitle);
                        double latitude = (double) sqlite3_column_double(statement, poi_latitude_degrees);
                        double longitude = (double) sqlite3_column_double(statement, poi_longitude_degrees);
                        int isInterior = (int) sqlite3_column_int(statement, poi_is_interior);
                        char *interiorId = (char *) sqlite3_column_text(statement, poi_interior_id);
                        int floor = (int) sqlite3_column_int(statement, poi_floor);
                        double height_terrain = (double) sqlite3_column_double(statement, poi_height_terrain);
                        char * iconKey = (char *) sqlite3_column_text(statement, poi_icon_key);
                        char * tags = (char *) sqlite3_column_text(statement, poi_tags);
                        char * readableTags = (char *) sqlite3_column_text(statement, poi_readable_tags);
                        char * userData = (char *) sqlite3_column_text(statement, poi_user_data);
                        
                        Eegeo::Space::LatLong location = Eegeo::Space::LatLong::FromDegrees(latitude, longitude);
                        std::string indoorId = interiorId;
                        const Search::SdkModel::TagIconKey& tagIconKey = iconKey;
                        
                        std::vector<std::string> tagSet = GetTagsFromString(tags);;
                        std::vector<std::string> humanReadableTags = GetTagsFromString(readableTags);
                        
                        ExampleApp::Search::SdkModel::SearchResultModel searchResultModel = ExampleApp::Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                                                                                                            identifier,
                                                                                                                                            title,
                                                                                                                                            subtitle,
                                                                                                                                            location,
                                                                                                                                            height_terrain,
                                                                                                                                            isInterior,
                                                                                                                                            indoorId,
                                                                                                                                            floor,
                                                                                                                                            tagSet,
                                                                                                                                            humanReadableTags,
                                                                                                                                            tagIconKey,
                                                                                                                                            ExampleApp::Search::EegeoVendorName,
                                                                                                                                            userData,
                                                                                                                                            Eegeo::Helpers::Time::MillisecondsSinceEpoch());
                        
                        
                        outPutResults.push_back(searchResultModel);
                    }
                }
                return false;
            }

        }
    }
}
