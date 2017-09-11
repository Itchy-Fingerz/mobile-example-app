// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultPoiViewContainer.h"
#include "ISearchResultPoiView.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiViewInterop : public ISearchResultPoiView
            {
            private:
                SearchResultPoiViewContainer* m_pView;
                Eegeo::Helpers::CallbackCollection0 m_closeClickedCallbacks;
                Eegeo::Helpers::CallbackCollection1<Search::SdkModel::SearchResultModel> m_togglePinClickedCallbacks;
                Eegeo::Helpers::CallbackCollection2<const Search::SdkModel::SearchResultModel&, const std::string&> m_availabilityChangedCallbacks;
                Eegeo::Helpers::CallbackCollection1<Search::SdkModel::SearchResultModel> m_showMeWayClickedCallbacks;
                Eegeo::Helpers::CallbackCollection2<Search::SdkModel::SearchResultModel,Search::SdkModel::SearchResultModel> m_showMeGateClickedCallbacks;
                std::string m_timeState;



            public:
                SearchResultPoiViewInterop(SearchResultPoiViewContainer* pView);

                void Show(const Search::SdkModel::SearchResultModel& model,
                          bool isPinned, std::string timeState);

                void Hide();
                
                void UpdateImage(const std::string& url,
                                 bool hasImage,
                                 const std::vector<Byte>* pImageBytes);
                
                void InsertAvailabilityChangedCallback(Eegeo::Helpers::ICallback2<const Search::SdkModel::SearchResultModel&, const std::string&>& callback);
                
                void RemoveAvailabilityChangedCallback(Eegeo::Helpers::ICallback2<const Search::SdkModel::SearchResultModel&, const std::string&>& callback);
                
                void HandleAvailabilityChanged(const Search::SdkModel::SearchResultModel& searchResultModel, const std::string& availability);

                void InsertClosedCallback(Eegeo::Helpers::ICallback0& callback);

                void RemoveClosedCallback(Eegeo::Helpers::ICallback0& callback);

                void HandleCloseClicked();
                
                void InsertTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                
                void RemoveTogglePinnedCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                
                void HandlePinToggleClicked(Search::SdkModel::SearchResultModel& searchResultModel);
                
                void InsertShowMeWayCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                
                void RemoveShowMeWayCallback(Eegeo::Helpers::ICallback1<Search::SdkModel::SearchResultModel>& callback);
                
                void HandleShowMeWayClicked(Search::SdkModel::SearchResultModel searchResultModel);
                
                void InsertShowMeGateCallback(Eegeo::Helpers::ICallback2<Search::SdkModel::SearchResultModel,Search::SdkModel::SearchResultModel>& callback);
                
                void RemoveShowMeGateCallback(Eegeo::Helpers::ICallback2<Search::SdkModel::SearchResultModel,Search::SdkModel::SearchResultModel>& callback);
                
                void HandleShowMeGateClicked(Search::SdkModel::SearchResultModel startPoiModel , Search::SdkModel::SearchResultModel endPoiModel);
                std::string CurrentTimeState()
                {
                    return m_timeState;
                }


            };
        }
    }
}
