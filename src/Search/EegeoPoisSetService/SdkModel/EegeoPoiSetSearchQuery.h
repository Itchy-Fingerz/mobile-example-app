// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "Types.h"
#include "IEegeoPoiSetSearchQuery.h"
#include "Web.h"
#include "SearchQuery.h"
#include "WebLoadRequestCompletionCallback.h"
#include "UrlHelpers.h"
#include "InteriorId.h"

#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPoisSetService
        {
            namespace SdkModel
            {
                class EegeoPoiSetSearchQuery : public IEegeoPoiSetSearchQuery, private Eegeo::NonCopyable
                {
                    Eegeo::Helpers::ICallback0& m_completionCallback;
                    std::string m_responseString;
                    bool m_isSuccess;
                    Eegeo::Web::TWebLoadRequestCompletionCallback<EegeoPoiSetSearchQuery> m_webRequestCompleteCallback;
                    Eegeo::Web::IWebLoadRequest* m_pWebLoadRequest;
                public:
                    EegeoPoiSetSearchQuery(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                           const std::string& serviceUrl,
                                           Eegeo::Helpers::ICallback0& completionCallback);
                    
                    ~EegeoPoiSetSearchQuery();
                    
                    void Cancel();
                    
                    bool IsSucceeded();
                    
                    const std::string& ResponseString();
                    
                private:
                    void OnWebResponseReceived(Eegeo::Web::IWebResponse& webResponse);
                };
            }
        }
    }
}
