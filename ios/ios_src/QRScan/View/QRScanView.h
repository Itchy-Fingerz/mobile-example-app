// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "QRScan.h"
#include "AppRunner.h"
#import "HeaderView.h"
#include "ViewController.h"
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>

@class QRScanView;
@class QRScanViewController;

@interface QRScanView : UIView <UIGestureRecognizerDelegate,AVCaptureMetadataOutputObjectsDelegate>
{
    ExampleApp::QRScan::View::QRScanViewInterop* m_pInterop;
    float m_stateChangeAnimationTimeSeconds;
    
}

- (id) initView;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

- (ExampleApp::QRScan::View::QRScanViewInterop*) getInterop;

@property (nonatomic, retain) HeaderView* pHeaderView;

@property (nonatomic, retain) UIView* pContentView;
@property (nonatomic, retain) UIView *pViewforCamera;
@property (nonatomic)  Boolean pIsReading;
@property (nonatomic, retain) CAShapeLayer *pOverlay;



-(BOOL)startReading;

-(void)stopReading;

-(void)playBeepSound;

@property (nonatomic, strong) AVCaptureSession *pCaptureSession;

@property (nonatomic, strong) AVCaptureVideoPreviewLayer *pVideoPreviewLayer;



@end
