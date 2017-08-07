// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "SearchResultPoiView.h"
#include "SearchResultPoiViewInterop.h"

@class EegeoSearchResultCheckInPoiView;

@interface EegeoSearchResultCheckInPoiView : UIView<SearchResultPoiView>

{
    UIViewController* m_pController;
    ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* m_pInterop;
    float m_stateChangeAnimationTimeSeconds;

}

@property (retain, nonatomic) IBOutlet UILabel *pTitleLbl;

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*) getInterop;

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned;

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;

- (void) setFullyActive;

- (void) setFullyInactive;

+(EegeoSearchResultCheckInPoiView *)EegeoSearchResultCheckInPoiViewWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop;

@end
