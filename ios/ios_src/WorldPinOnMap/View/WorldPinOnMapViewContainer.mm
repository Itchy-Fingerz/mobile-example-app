// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinOnMapViewContainer.h"
#include <algorithm>
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "WorldPinOnMapViewInterop.h"
#include "SearchVendorNames.h"

@implementation WorldPinOnMapViewContainer

- (id)initWithParams:(float)pinDiameter :(float)pixelScale :(ImageStore*)pImageStore
{
    self = [super init];
    
    if(self)
    {
        m_pInterop = new ExampleApp::WorldPins::View::WorldPinOnMapViewInterop(self);
        
        self.pYelpHovercard = [[YelpHovercardView alloc]initWithParams:pinDiameter :pixelScale :m_pInterop];
        
        self.pInteriorHovercard = [[InteriorsHovercard alloc]initWithParams:pinDiameter*1.5f :pixelScale :m_pInterop];
        
        self.pTourHovercard = [[TourHovercardView alloc]initWithParams:pinDiameter :pixelScale :pImageStore :m_pInterop];
        
        self.pTwitterHovercard = [[TwitterWorldHovercard alloc]initWithParams:pinDiameter :pixelScale :pImageStore :m_pInterop];
        
        self.pTwitterTourHovercard = [[TwitterTourHovercard alloc]initWithParams:pinDiameter :pixelScale :pImageStore :m_pInterop];
        
        self.pCurrentHovercard = nil;
        
        m_screenWidth = self.superview.bounds.size.width;
        m_screenHeight = self.superview.bounds.size.height;
        self.frame = CGRectMake(0, 0, m_screenWidth, m_screenHeight);
    }
    
    return self;
}

- (void)dealloc
{
    if(self.pCurrentHovercard != nil)
    {
        [self.pCurrentHovercard removeFromSuperview];
    }
    [self.pTwitterTourHovercard release];
    [self.pTwitterHovercard release];
    [self.pTourHovercard release];
    [self.pInteriorHovercard release];
    [self.pYelpHovercard release];
    
    Eegeo_DELETE m_pInterop;
    
    [self removeFromSuperview];
    [super dealloc];
}

- (ExampleApp::WorldPins::View::WorldPinOnMapViewInterop*) getInterop
{
    return m_pInterop;
}

- (void)layoutSubviews
{
    m_screenWidth = self.superview.bounds.size.width;
    m_screenHeight = self.superview.bounds.size.height;
    [self setFrame:CGRectMake(0, 0, m_screenWidth, m_screenHeight)];
}

- (void) setContent:(const ExampleApp::WorldPins::SdkModel::IWorldPinsInFocusModel&) worldPinsInFocusModel
{
    if(self.pCurrentHovercard != nil)
    {
        [self.pCurrentHovercard removeFromSuperview];
    }
    
    if(worldPinsInFocusModel.GetVendor() == ExampleApp::Search::YelpVendorName ||
       worldPinsInFocusModel.GetVendor() == ExampleApp::Search::GeoNamesVendorName ||
       worldPinsInFocusModel.GetVendor() == ExampleApp::Search::MyPinVendorName)
    {
        self.pCurrentHovercard = self.pYelpHovercard;
    }
    else if(worldPinsInFocusModel.GetVendor() == ExampleApp::Search::InteriorVendorName)
    {
        self.pCurrentHovercard = self.pInteriorHovercard;
    }
    else if(worldPinsInFocusModel.GetVendor() == ExampleApp::Search::WorldTwitterVendorName)
    {
        self.pCurrentHovercard = self.pTwitterHovercard;
    }
    else if(worldPinsInFocusModel.GetVendor() == ExampleApp::Search::ExampleTourVendorName)
    {
        self.pCurrentHovercard = self.pTourHovercard;
    }
    else if (worldPinsInFocusModel.GetVendor() == ExampleApp::Search::TourTwitterVendorName)
    {
        self.pCurrentHovercard = self.pTwitterTourHovercard;
    }
    [self addSubview:self.pCurrentHovercard];
    [self.pCurrentHovercard setContent:worldPinsInFocusModel];
    [self setNeedsLayout];
}

- (void) setFullyActive :(float)modality
{
    self.userInteractionEnabled = YES;
    [self.pTwitterTourHovercard setFullyActive:modality];
    [self.pTwitterHovercard setFullyActive:modality];
    [self.pTourHovercard setFullyActive:modality];
    [self.pInteriorHovercard setFullyActive:modality];
    [self.pYelpHovercard setFullyActive:modality];
}

- (void) setFullyInactive
{
    self.userInteractionEnabled = NO;
    [self.pTwitterTourHovercard setFullyInactive];
    [self.pTwitterHovercard setFullyInactive];
    [self.pTourHovercard setFullyInactive];
    [self.pInteriorHovercard setFullyInactive];
    [self.pYelpHovercard setFullyInactive];
}

- (void) updatePosition:(float)x :(float)y
{
    if(self.pCurrentHovercard != nil)
    {
        [self.pCurrentHovercard updatePosition:x :y];
    }
}

- (BOOL)consumesTouch:(UITouch *)touch
{
    if(self.userInteractionEnabled && self.pCurrentHovercard != nil)
    {
        CGPoint touchLocation = [touch locationInView:self];
        return CGRectContainsPoint(self.pCurrentHovercard.frame, touchLocation);
    }
    
    return false;
}


- (void) updateScreenState:(float)onScreenState
{
    if(self.pCurrentHovercard != nil)
    {
        [self.pCurrentHovercard setAlpha:onScreenState];
    }

}

- (void) updateScreenStateAndVisibility:(float)onScreenState
{
    if(self.pCurrentHovercard != nil)
    {
        [self.pCurrentHovercard setAlpha:onScreenState];
    }
    
}

@end