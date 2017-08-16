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
                size_t uiLevenshteinDistance(const std::string &s1, const std::string &s2)
                {
                    const size_t m(s1.size());
                    const size_t n(s2.size());
                    
                    if( m==0 ) return n;
                    if( n==0 ) return m;
                    
                    size_t *costs = new size_t[n + 1];
                    
                    for( size_t k=0; k<=n; k++ ) costs[k] = k;
                    
                    size_t i = 0;
                    for ( std::string::const_iterator it1 = s1.begin(); it1 != s1.end(); ++it1, ++i )
                    {
                        costs[0] = i+1;
                        size_t corner = i;
                        
                        size_t j = 0;
                        for ( std::string::const_iterator it2 = s2.begin(); it2 != s2.end(); ++it2, ++j )
                        {
                            size_t upper = costs[j+1];
                            if( *it1 == *it2 )
                            {
                                costs[j+1] = corner;
                            }
                            else
                            {
                                size_t t(upper<corner?upper:corner);
                                costs[j+1] = (costs[j]<t?costs[j]:t)+1;
                            }
                            
                            corner = upper;
                        }
                    }
                    
                    size_t result = costs[n];
                    delete [] costs;
                    
                    return result;
                }
                
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
