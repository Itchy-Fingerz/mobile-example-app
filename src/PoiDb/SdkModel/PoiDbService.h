// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include <string>

#include "IPoiDbService.h"
#include "Types.h"
#include "Sqlite.h"
#include "InteriorInteractionModel.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            class PoiDbService: public IPoiDbService, private Eegeo::NonCopyable
            {
            private:
                
                Sqlite::SqliteTable& m_sqliteDbTable;
                Sqlite::SqliteTable& m_venueLabelTable;
                
                Sqlite::SqliteQueryBuilder& m_sqliteQueryBuilder;
                const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
                
            public:
                PoiDbService(Sqlite::SqliteDbConnection* pSqliteDbConnection, Sqlite::SqliteTable* pSqliteDbTable, Sqlite::SqliteTable* pSqliteVenueDbTable, Sqlite::SqliteQueryBuilder* pSqliteQueryBuilder, const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);

                ~PoiDbService();
                
                virtual void FetchPoisWithQuery(const Search::SdkModel::SearchQuery& query,std::vector<Search::SdkModel::SearchResultModel>& outPutResults);
                virtual void FetchVenuesLabelsWithQuery(std::vector<Search::SdkModel::SearchResultModel>& outPutResults);
                virtual void FetchSuggestionForAutoComplete(const std::string& query, std::vector<Search::SdkModel::SearchResultModel>& outPutResults);

            };
        }
    }
}
