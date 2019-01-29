// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "QRScan.h"
#include "AppRunner.h"
#import "HeaderView.h"
#include "ViewController.h"

@class QRScanView;
@class QRScanViewController;

@interface QRScanView : UIView <UIGestureRecognizerDelegate>
{
    ExampleApp::QRScan::View::QRScanViewInterop* m_pInterop;
    float m_stateChangeAnimationTimeSeconds;
}

- (id) initView;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const std::string*)content;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

- (void) showHiddenText:(UILongPressGestureRecognizer*)gesture;

- (ExampleApp::QRScan::View::QRScanViewInterop*) getInterop;

@property (nonatomic, retain) HeaderView* pHeaderView;

@property (nonatomic, retain) UILabel* pTextContent;
@property (nonatomic, retain) UIView* pContentSeperator;
@property (nonatomic, retain) UILabel* pDevelopedByLabel;
@property (nonatomic, retain) UIImageView* pWrldLogoImage;
@property (nonatomic, retain) UIScrollView* pContentScrollView;
@property (nonatomic, retain) UIView* pContentView;

@property (nonatomic, retain) UIButton* pLegalLink;
@property (nonatomic, retain) UIButton* pPrivacyLink;
@property (nonatomic, retain) UIButton* pEulaLink;
@property (nonatomic, retain) UIButton* pTeamLink;

@end
