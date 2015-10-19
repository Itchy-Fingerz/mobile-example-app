// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSYelpSearchQueryFactory.h"
#include "iOSYelpSearchQuery.h"
#include "iOSYelpBusinessQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            iOSYelpSearchQueryFactory::iOSYelpSearchQueryFactory(const std::string& yelpConsumerKey,
                                                                 const std::string& yelpConsumerSecret,
                                                                 const std::string& yelpOAuthToken,
                                                                 const std::string& yelpOAuthTokenSecret,
                                                                 SdkModel::IYelpCategoryMapper& yelpCategoryMapper)
            : m_yelpConsumerKey(yelpConsumerKey)
            , m_yelpConsumerSecret(yelpConsumerSecret)
            , m_yelpOAuthToken(yelpOAuthToken)
            , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
            , m_yelpCategoryMapper(yelpCategoryMapper)
            {
            }
            
            iOSYelpSearchQueryFactory::~iOSYelpSearchQueryFactory()
            {
            }
            
            SdkModel::IYelpSearchQuery* iOSYelpSearchQueryFactory::CreateYelpSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                                  Eegeo::Helpers::ICallback0& completionCallback)
            
            {
                return Eegeo_NEW(iOSYelpSearchQuery)(m_yelpConsumerKey,
                                                     m_yelpConsumerSecret,
                                                     m_yelpOAuthToken,
                                                     m_yelpOAuthTokenSecret,
                                                     query,
                                                     completionCallback);
            }
            
            SdkModel::IYelpSearchQuery* iOSYelpSearchQueryFactory::CreateYelpSearchForSpecificLocation(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                                                             Eegeo::Helpers::ICallback1<const ExampleApp::Search::SdkModel::IdentitySearchCallbackData&>& callback)
            
            {
                return Eegeo_NEW(iOSYelpBusinessQuery)(m_yelpConsumerKey,
                                                       m_yelpConsumerSecret,
                                                       m_yelpOAuthToken,
                                                       m_yelpOAuthTokenSecret,
                                                       m_yelpCategoryMapper,
                                                       outdatedSearchResult,
                                                       callback);
            }
        }
    }
}

