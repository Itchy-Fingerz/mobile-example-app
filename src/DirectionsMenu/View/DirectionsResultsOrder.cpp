// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <limits>
#include <map>

#include "DirectionsResultsOrder.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"

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
            }
            
            bool DirectionsResultsOrder::operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
            {
                //return VendorPriority(a.GetVendor()) < VendorPriority(b.GetVendor());
                
                size_t distanceFromFirst = levenshtein_distance(m_queryString.c_str(),m_queryString.size(),a.GetTitle().c_str(),m_queryString.size());
                
                size_t distanceFromSecond = levenshtein_distance(m_queryString.c_str(),m_queryString.size(),b.GetTitle().c_str(),m_queryString.size());                
                
                return distanceFromFirst < distanceFromSecond;
                
            }
        }
    }
}
