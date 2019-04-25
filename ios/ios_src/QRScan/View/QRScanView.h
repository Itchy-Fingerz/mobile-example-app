// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include "QRScan.h"
#include "AppRunner.h"
#import "HeaderView.h"
#include "ViewController.h"
#import <AVFoundation/AVFoundation.h>
#import <AudioToolbox/AudioToolbox.h>
#include "BidirectionalBus.h"

@class QRScanView;
@class QRScanViewController;

@interface QRScanView : UIView <UIGestureRecognizerDelegate,AVCaptureMetadataOutputObjectsDelegate>
{
    ExampleApp::QRScan::View::QRScanViewInterop* m_pInterop;
    float m_stateChangeAnimationTimeSeconds;
    
}


+(QRScanView*)loadQRScanViewWithBus:(ExampleApp::ExampleAppMessaging::TMessageBus&) messageBus;


- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setFullyActive;

- (void) setFullyInactive;

- (void) setActiveStateToIntermediateValue:(float)activeState;

- (ExampleApp::QRScan::View::QRScanViewInterop*) getInterop;

@property (retain, nonatomic) IBOutlet UIImageView *pQrDetectedImageView;
@property (retain, nonatomic) IBOutlet UIButton *pCloseButton;

@property (nonatomic, retain) IBOutlet UIView* pCameraContentView;
@property (nonatomic, retain) IBOutlet UIView* pViewforCameraLayer;
@property (nonatomic)  Boolean pIsReading;
@property (nonatomic)  Boolean pIsScanningDone;
@property (nonatomic, retain) CAShapeLayer *pOverlay;
@property (retain, nonatomic) IBOutlet UILabel *pUseCameraLabel;
@property (retain, nonatomic) IBOutlet UILabel *pQrdetactedLabel;
@property (retain, nonatomic) IBOutlet UILabel *pTransitionLabel;



-(BOOL)startReading;

-(void)stopReading;

-(void)playBeepSound;

@property (nonatomic, strong) AVCaptureSession *pCaptureSession;

@property (nonatomic, strong) AVCaptureVideoPreviewLayer *pVideoPreviewLayer;



@end