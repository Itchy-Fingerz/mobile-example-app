//
// Created by Najhi Ullah on 09/08/2018.
//

#include "IDataSetInsertQuery.h"
#include <string.h>
#include "Web.h"
#include "WebLoadRequestCompletionCallback.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace DataSet
    {
        namespace SdkModel
        {
            class DataSetInsertQuery : public IDataSetInsertQuery
            {
            private:
                Eegeo::Web::IWebLoadRequest* m_pWebLoadRequest;
                Eegeo::Web::TWebLoadRequestCompletionCallback<DataSetInsertQuery> m_webRequestCompleteCallback;
                Eegeo::Helpers::ICallback0& m_completionCallback;

                void HandleWebResponseComplete(Eegeo::Web::IWebResponse& webResponse);

                bool m_dispatched;

                bool m_isSuccess;

                std::string m_responseString;

            public:
                DataSetInsertQuery(const std::string &name, const Eegeo::Web::WebPostData &webPostData,
                                     Eegeo::Web::IWebLoadRequestFactory &webRequestFactory,
                                     Eegeo::Helpers::ICallback0 &completionCallback);
                ~DataSetInsertQuery();

                void Dispatch();

                void Cancel();

                bool IsSucceeded();

                const std::string& ResponseString();
            };
        }
    }
}
