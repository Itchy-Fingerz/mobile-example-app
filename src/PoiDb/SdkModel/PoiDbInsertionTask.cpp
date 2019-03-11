// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiDbInsertionTask.h"
#include "SqliteDbConnection.h"
#include "SqliteQueryBuilder.h"
#include "SqliteTable.h"
#include "EegeoPoiSetSearchService.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            std::string GetStringForTags(const std::vector<std::string>& tags)
            {
                std::string returnString = "";
                for(size_t i = 0; i < tags.size(); i++)
                {
                    returnString += tags[i];
                    if(i < (tags.size()-1))
                    {
                        returnString += ",";
                    }
                }
                return returnString;
            }
            
            PoiDbInsertionTask::PoiDbInsertionTask(const std::vector<Search::SdkModel::SearchResultModel>& results, Sqlite::SqliteQueryBuilder* pSqliteQueryBuilder, Sqlite::SqliteTable* pTable)
            : m_results(results)
            , m_sqliteQueryBuilder(*pSqliteQueryBuilder)
            , m_table(*pTable)
            {
                
            }
            
            PoiDbInsertionTask::~PoiDbInsertionTask() {
                
            }
            
            void PoiDbInsertionTask::DoWork()
            {
//                const std::vector<Search::SdkModel::SearchResultModel> results = message.GetResults();
                
                for (std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = m_results.begin();
                     it != m_results.end();
                     it++)
                {
                    const Search::SdkModel::SearchResultModel &searchResult = *it;
                    
                    std::string tagsString = GetStringForTags(searchResult.GetTags());
                    std::string readableTagsString = GetStringForTags(searchResult.GetHumanReadableTags());
                    
                    Sqlite::SqliteTableQuery createTableQuery = m_sqliteQueryBuilder.BuildQuery_CreateInsertRecord(m_table, searchResult.GetIdentifier(), searchResult.GetTitle(), searchResult.GetSubtitle(), searchResult.GetLocation().GetLatitudeInDegrees(), searchResult.GetLocation().GetLongitudeInDegrees(), searchResult.IsInterior(), searchResult.GetBuildingId().Value(), searchResult.GetFloor(), searchResult.GetHeightAboveTerrainMetres(), searchResult.GetIconKey(), tagsString, readableTagsString, searchResult.GetJsonData());
                    
                    createTableQuery.Execute();
                }
                
            }
            
            void PoiDbInsertionTask::DoFinalizeOnMainThread()
            {
                
            }
        }
    }
}
