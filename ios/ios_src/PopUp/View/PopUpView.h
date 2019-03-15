// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "PopUp.h"
#include "AppRunner.h"
#include "ViewController.h"

@class PopUpView;
@class PopUpViewController;

@interface PopUpView : UIView <UIGestureRecognizerDelegate>
{
    ExampleApp::PopUp::View::PopUpViewInterop* m_pInterop;
    float m_stateChangeAnimationTimeSeconds;
    float m_pixelScale;
    
    bool m_isOpen;
}

- (id) initView:(float) pixelScale;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setPosition:(double)x ndY:(double)y;

- (void) setFullyActive;

- (void) setFullyInactive;

- (ExampleApp::PopUp::View::PopUpViewInterop*) getInterop;

@property (nonatomic, retain) UIImageView* pYouAreHereImage;

@end
