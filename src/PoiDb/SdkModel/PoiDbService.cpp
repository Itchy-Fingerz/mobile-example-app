// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiDbService.h"
#include "SqliteDbConnection.h"
#include "SqliteTable.h"
#include "SqliteQueryBuilder.h"
#include "SearchResultModel.h"
#include "SearchQuery.h"
#include "SqliteTableQuery.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            PoiDbService::PoiDbService(Sqlite::SqliteDbConnection* pSqliteDbConnection, Sqlite::SqliteTable* pSqliteDbTable, Sqlite::SqliteTable* pSqliteVenueDbTable, Sqlite::SqliteQueryBuilder* pSqliteQueryBuilder, const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
            : m_sqliteDbTable(*pSqliteDbTable)
            , m_venueLabelTable(*pSqliteVenueDbTable)
            , m_sqliteQueryBuilder(*pSqliteQueryBuilder)
            , m_interiorInteractionModel(interiorInteractionModel)
            {
            }
            
            PoiDbService::~PoiDbService()
            {
            }
            
            void PoiDbService::FetchPoisWithQuery(const Search::SdkModel::SearchQuery& query, std::vector<Search::SdkModel::SearchResultModel>& outPutResults)
            {
                Sqlite::SqliteTableQuery fetchRecordsQuery = m_sqliteQueryBuilder.BuildQuery_FetchRecords(m_sqliteDbTable, query.Query(), query.IsTag(), m_interiorInteractionModel.HasInteriorModel(), m_interiorInteractionModel.GetSelectedFloorIndex());
                
                fetchRecordsQuery.Execute(outPutResults);                
                return;
            }
            
            void PoiDbService::FetchVenuesLabelsWithQuery(std::vector<Search::SdkModel::SearchResultModel>& outPutResults)
            {
                Sqlite::SqliteTableQuery fetchRecordsQuery = m_sqliteQueryBuilder.BuildQuery_FetchRecordsForLabels(m_venueLabelTable, m_interiorInteractionModel.GetSelectedFloorIndex());
                
                fetchRecordsQuery.Execute(outPutResults);
                return;
            }
        }
    }
}
