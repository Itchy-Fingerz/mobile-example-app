// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#import <UIKit/UIKit.h>
#include "CustomAlertViewIncludes.h"


@class CustomAlertView;

@interface CustomAlertView : UIView
{
    ExampleApp::CustomAlert::View::CustomAlertViewInterop* m_pInterop;
    UIViewController* m_pController;
    
    float m_screenWidth;
    float m_screenHeight;
    UIView *customAlertView;
}

- (id) initWithDimensions:(float)width
                         :(float)height
                         :(float)pixelScale;

- (ExampleApp::CustomAlert::View::CustomAlertViewInterop*) getInterop;

- (BOOL)consumesTouch:(UITouch *)touch;


@end
