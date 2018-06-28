// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "Search.h"
#include "ICallback.h"
#include "SearchResultModel.h"
#include "YelpSearchQueryFactory.h"
#include "YelpSearchQuery.h"
#include "YelpSearchConstants.h"
#include "YelpCategoryModel.h"


#include "urlencode.h"
#include <sstream>
#include <iomanip>

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                namespace
                {
                    
                    std::string UrlGetParamsEncoder(const std::map<std::string, std::string>& params)
                    {
                        std::string url;
                        
                        for (std::map<std::string, std::string>::const_iterator it = params.begin();
                             it != params.end();
                             ++it)
                        {
                            url += it->first + "=" + urlencode(it->second, URLEncodeType::URLEncode_Everything) + "&";
                        }
                        
                        //remove trailing &
                        url[url.length() - 1] = '\0';
                        
                        return url;
                    }
                    
                    
                }
                YelpSearchQueryFactory::YelpSearchQueryFactory(
                    const std::string& yelpApiKey,
                    SdkModel::SearchTagToYelpCategoryMapper& searchTagToYelpCategoryMap,
                    Eegeo::Web::IWebLoadRequestFactory& webRequestFactory)
                : m_webRequestFactory(webRequestFactory)
                , m_yelpApiKey(yelpApiKey)
                , m_searchTagToYelpCategoryMap(searchTagToYelpCategoryMap)
                , m_apiUrl("https://api.yelp.com/v3/businesses/search")
                {

                }

                YelpSearchQueryFactory::~YelpSearchQueryFactory()
                {
                }

                SdkModel::IYelpSearchQuery* YelpSearchQueryFactory::CreateYelpSearchForQuery(const Search::SdkModel::SearchQuery& searchQuery,
                    Eegeo::Helpers::ICallback0 &completionCallback)
                {
                    std::string searchTerm = "";
                    YelpCategoryModel categoryFilter { "", true };
                    std::string searchLimit("20");
                    
                    if (searchQuery.IsTag())
                    {
                        m_searchTagToYelpCategoryMap.TryGetBestYelpCategoryForSearchTag(searchQuery.Query(), categoryFilter);
                        if(categoryFilter.skipYelpSearch == true)
                        {
                            searchLimit = "0";
                        }
                    }
                    else
                    {
                        searchTerm = searchQuery.Query();
                    }
                    
                    std::map<std::string, std::string> params;
                    std::stringstream conversionStream;
                    
                    conversionStream.setf(std::ios::fixed);
                    conversionStream << std::setprecision(17)
                                     << searchQuery.Location().GetLatitudeInDegrees();
                    std::string latitude = conversionStream.str();
                    
                    conversionStream.clear();
                    conversionStream.str("");
                    conversionStream << std::setprecision(17)
                                     << searchQuery.Location().GetLongitudeInDegrees();
                    std::string longitude = conversionStream.str();
                    
                    if (searchTerm.length() > 0)
                    {
                        params["term"] = searchTerm;
                    }

                    if (categoryFilter.yelpCategoryFilter.length() > 0)
                    {
                        params["categories"] = categoryFilter.yelpCategoryFilter;
                    }
                    params["latitude"] = latitude;
                    params["longitude"] = longitude;
                    params["limit"] = searchLimit;
                    
                    std::stringstream requestUrl;
                    requestUrl << m_apiUrl << "?" << UrlGetParamsEncoder(params);
                    
                    return Eegeo_NEW(YelpSearchQuery)(
                        requestUrl.str(),
                        m_yelpApiKey,
                        completionCallback,
                        m_webRequestFactory);
                }


            }
        }
    }
}
