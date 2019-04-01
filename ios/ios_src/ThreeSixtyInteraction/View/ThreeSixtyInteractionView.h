//
//  EegeoSearchResultPoiWeb.h
//  ExampleApp
//
//  Created by Sohail Khan on 1/14/19.
//

#import <UIKit/UIKit.h>
#include <vector>
#include "ThreeSixtyInteractionViewIncludes.h"


@interface ThreeSixtyInteractionView: UIView
{
    UIViewController* m_pController;
    float m_stateChangeAnimationTimeSeconds;
    ExampleApp::ThreeSixtyInteraction::View::ThreeSixtyInteractionViewInterop* m_pInterop;
    UIWebView *m_pWebView;
}
@property (retain, nonatomic) IBOutlet UIButton *m_pCloseButton;
@property (retain, nonatomic) IBOutlet UIActivityIndicatorView *m_pSpinner;

+ (id)initView;

- (ExampleApp::ThreeSixtyInteraction::View::ThreeSixtyInteractionViewInterop*) getInterop;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(std::string)url;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

@end
