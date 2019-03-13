// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "PoiDb.h"
#include "Search.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace PoiDb
    {
        namespace SdkModel
        {
            class IPoiDbLoader
            {
            public:
                virtual ~IPoiDbLoader() { }
                virtual void CreateDbConnection() = 0;
                virtual void ResultsReceived(const bool& didSucceed, const std::vector<Search::SdkModel::SearchResultModel>& results) = 0;
                virtual void InsertOnDbServiceStartedCallback(Eegeo::Helpers::ICallback1<IPoiDbService*>& callback) = 0;
                virtual void RemoveOnPerformedQueryCallback(Eegeo::Helpers::ICallback1<IPoiDbService*>& callback) = 0;
            };
        }
    }
}
