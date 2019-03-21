//
//  EegeoSearchResultPoiWeb.h
//  ExampleApp
//
//  Created by Sohail Khan on 1/14/19.
//

#import <UIKit/UIKit.h>
#include <vector>
#include "SearchResultPoiView.h"
#include "SearchResultPoiViewInterop.h"
#include "SearchResultModel.h"
#include "EegeoSearchResultModel.h"


@interface EegeoSearchResultPoiWebView : UIView<SearchResultPoiView>
{
    UIViewController* m_pController;
    float m_stateChangeAnimationTimeSeconds;
    ExampleApp::Search::SdkModel::SearchResultModel m_model;
    ExampleApp::Search::EegeoPois::SdkModel::EegeoSearchResultModel m_eegeoModel;
    ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop* m_pInterop;

}
@property (retain, nonatomic) IBOutlet UIButton *m_pCloseButton;
@property (retain, nonatomic) IBOutlet UIWebView *m_pWebView;
@property (retain, nonatomic) IBOutlet UIActivityIndicatorView *m_pSpinner;

+ (id)initWithInterop:(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)pInterop;

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned;

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

@end
