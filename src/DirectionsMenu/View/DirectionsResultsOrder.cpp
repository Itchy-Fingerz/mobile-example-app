// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <limits>
#include <map>

#include "DirectionsResultsOrder.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "SearchResultSectionOrder.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace View
        {
            namespace
            {
                size_t levenshtein_distance(const char* s, size_t n, const char* t, size_t m)
                {
                    ++n; ++m;
                    size_t* d = new size_t[n * m];
                    
                    memset(d, 0, sizeof(size_t) * n * m);
                    
                    for (size_t i = 1, im = 0; i < m; ++i, ++im)
                    {
                        for (size_t j = 1, jn = 0; j < n; ++j, ++jn)
                        {
                            if (s[jn] == t[im])
                            {
                                d[(i * n) + j] = d[((i - 1) * n) + (j - 1)];
                            }
                            else
                            {
                                d[(i * n) + j] = fmin(d[(i - 1) * n + j] + 1, /* A deletion. */
                                                      fmin(d[i * n + (j - 1)] + 1, /* An insertion. */
                                                           d[(i - 1) * n + (j - 1)] + 1)); /* A substitution. */
                            }
                        }
                    }
                    
                    size_t r = d[n * m - 1];
                    
                    delete [] d;
                    
                    return r;
                }
                
                int VendorPriority(const std::string& vendor)
                {
                    const int HighestPriority = std::numeric_limits<int>::max();
                    enum AscendingVendorPriority {
                        EegeoVendorPriority,
                        YelpVendorPriority,
                        GeoNamesVendorPriority
                    };
                    
                    static const std::map<std::string, int> vendorPriorities{
                        {Search::EegeoVendorName,    EegeoVendorPriority},
                        {Search::YelpVendorName,     YelpVendorPriority},
                        {Search::GeoNamesVendorName, GeoNamesVendorPriority}};
                    
                    const std::map<std::string, int>::const_iterator vendorIx = vendorPriorities.find(vendor);
                    return vendorIx != vendorPriorities.end()
                    ? vendorIx->second
                    : HighestPriority;
                }
                
                size_t GetMinimumDistance(const Search::SdkModel::SearchResultModel& searchModel,std::string queryString)
                {
                    size_t distanceFromTitle = levenshtein_distance(queryString.c_str(),queryString.size(),searchModel.GetTitle().c_str(),queryString.size());
                    
                    size_t minimumdistance = distanceFromTitle;
                    
                    for (std::vector<std::string>::const_iterator iterator = searchModel.GetTags().begin(); iterator != searchModel.GetTags().end(); iterator++) {
                        
                        std::string tag = *iterator;
                    size_t distanceFromTag = levenshtein_distance(queryString.c_str(),queryString.size(),tag.c_str(),queryString.size());
                        
                        if (distanceFromTag < minimumdistance)
                        {
                            minimumdistance = distanceFromTag;
                        }
                    }
                    
                    return minimumdistance;
                }
            }
            
            bool DirectionsResultsOrder::operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
            {
                if(a.GetVendor() != b.GetVendor())
                {
                    return VendorPriority(a.GetVendor()) < VendorPriority(b.GetVendor());
                }
                else
                {
                    size_t distanceFromFirst = GetMinimumDistance(a, m_queryString);
                    
                    size_t distanceFromSecond = GetMinimumDistance(b, m_queryString);
                    
                    return distanceFromFirst < distanceFromSecond;
                }
                
            }
        }
    }
}
