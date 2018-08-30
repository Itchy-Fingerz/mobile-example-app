//
// Created by Najhi Ullah on 09/08/2018.
//

#include "DataSetInsertQuery.h"
#include "WebPostData.h"
#include "IWebLoadRequest.h"
#include "IWebLoadRequestFactory.h"

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            DataSetInsertQuery::DataSetInsertQuery(const std::string &apiUrl, const Eegeo::Web::WebPostData &webPostData,
                                                       Eegeo::Web::IWebLoadRequestFactory &webRequestFactory,
                                                       Eegeo::Helpers::ICallback0 &completionCallback)
            : m_pWebLoadRequest(NULL)
            , m_webRequestCompleteCallback(this, &DataSetInsertQuery::HandleWebResponseComplete)
            , m_dispatched(false)
            , m_completionCallback(completionCallback)
            {
                m_pWebLoadRequest = webRequestFactory
                        .Begin(Eegeo::Web::HttpVerbs::Values::POST, apiUrl, m_webRequestCompleteCallback)
                        .SetPostBodyData(webPostData)
                        .Build();
            }

            DataSetInsertQuery::~DataSetInsertQuery()
            {
            }

            void DataSetInsertQuery::Dispatch()
            {
                Eegeo_ASSERT(!m_dispatched, "DataSet Insert Query already dispatched");

                m_dispatched = true;

                m_pWebLoadRequest->Load();
            }

            void DataSetInsertQuery::Cancel()
            {
                Eegeo_ASSERT(m_dispatched, "Cannot cancel until DataSet Insert Query has been dispatched.\n");

                m_pWebLoadRequest->Cancel();

                Eegeo_DELETE this;
            }

            bool DataSetInsertQuery::IsSucceeded()
            {
                return m_isSuccess;
            }

            const std::string& DataSetInsertQuery::ResponseString()
            {
                return m_responseString;
            }

            void DataSetInsertQuery::HandleWebResponseComplete(Eegeo::Web::IWebResponse& webResponse)
            {
                Eegeo_ASSERT(!webResponse.IsCancelled());

                size_t resultSize = webResponse.GetBodyData().size();

                m_isSuccess = webResponse.IsSucceeded();

                m_responseString = (resultSize > 0) ? std::string(reinterpret_cast<char const*>(&(webResponse.GetBodyData().front())), resultSize) : "<empty>";

                std::string logStr = "Dataset: Response => " + m_responseString;
                Eegeo_TTY(logStr.c_str());

                m_completionCallback();

                Eegeo_DELETE this;
            }
        }
    }
}