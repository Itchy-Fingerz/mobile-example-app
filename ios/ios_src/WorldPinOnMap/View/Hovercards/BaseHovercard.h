// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#import <UIKit/UIKit.h>
#include <string>
#include "AppRunner.h"
#include "WorldPinOnMapViewIncludes.h"
#include "WorldPinOnMapView.h"
#include "IWorldPinsInFocusModel.h"

@class BaseHovercard;

@interface BaseHovercard : UIView <UIGestureRecognizerDelegate, WorldPinOnMapView>
{
    ExampleApp::WorldPins::View::WorldPinOnMapViewInterop* m_pInterop;
    UITapGestureRecognizer* m_tapGestureRecogniser;
    float m_stateChangeAnimationTimeSeconds;
    float m_pinOffset;
    float m_pixelScale;
    float m_previousX;
    float m_previousY;
    float m_cardHeight;
}

- (id) initWithParams:(float)pinDiameter :(float)pixelScale :(ExampleApp::WorldPins::View::WorldPinOnMapViewInterop*)interop :(float)fontSize;

- (BOOL) consumesTouch:(UITouch *)touch;

- (void) setContent:(const ExampleApp::WorldPins::SdkModel::IWorldPinsInFocusModel&) worldPinsInFocusModel;

- (void) setFullyActive :(float)modality;

- (void) setFullyInactive;

- (void) updatePosition:(float)x :(float)y;

- (UIView *) hitTest:(CGPoint)point withEvent:(UIEvent *)event;

@property (nonatomic, retain) UIView* pMainControlContainer;
@property (nonatomic, retain) UIView* pTopStrip;
@property (nonatomic, retain) UIView* pMainControlShadowContainer;
@property (nonatomic, retain) UIView* pArrowContainer;
@property (nonatomic, retain) UIView* pLabelBack;
@property (nonatomic, retain) UILabel* pNameLabel;

@end
