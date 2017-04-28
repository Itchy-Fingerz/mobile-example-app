//
<<<<<<< HEAD
//  SLGeomessengerDelegate.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
=======
//  SLGeoMessengerDelegate.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
//

#import <Foundation/Foundation.h>

<<<<<<< HEAD
@protocol SLGeomessenger;

/**
 To receive notifications for geomessenger, this protocol must be implemented.
 */
@protocol SLGeomessengerDelegate <NSObject>

/// @name Methods

/**
 Called when a geomessenger area is entered.
 
 @param geomessenger The geomessenger object handling the area entered.
 @param title Title of the area entered.
 @param message Message of the area entered.
 */
- (void)geomessenger:(id<SLGeomessenger>)geomessenger didEnterGeomessageWithTitle:(NSString *)title andMessage:(NSString *)message;

/**
 Called when a geomessenger area is left.
 
 @param geomessenger The geomessenger object handling the area left.
 @param title Title of the area left.
 @param message Message of the area left.
 */
- (void)geomessenger:(id<SLGeomessenger>)geomessenger didLeaveGeomessageWithTitle:(NSString *)title andMessage:(NSString *)message;


@optional
/**
 Optional
 
 Called if anything goes wrong with loading of the geomessenger areas.
 
 @param geomessenger The geomessenger object which failed loading.
 */
- (void)geomessengerDidFailLoadingGeomessages:(id<SLGeomessenger>)geomessenger;

@end
=======
@protocol SLGeoMessenger;
@class SLGeoMessengerZone;

/**
 The methods declared by the UIScrollViewDelegate protocol allows the adopting delegate to respond to messages from the SLGeoMessenger protocol. The protocol contains methods responding to events occuring during the startup of the SLGeoMessenger service and methods for continious GeoMessenger zone events.
 
 ### Note
 
 Errors from [SLGeoMessengerDelegate geoMessenger:didFailWithError:] are declared in SLGeoMessengerErrorType. If you get SLGeoMessengerErrorTypeLocationManagerNotLoaded you must restart SLGeoMessenger your self. The other error types will trigger a timer and will try again later.
 */
@protocol SLGeoMessengerDelegate <NSObject>

/// @name Startup events.

/**
 @abstract Called when the SLGeoMessenger have loaded and started.
 
 @param geoMessenger The SLGeoMessenger manager object that generated the update event.
 */
- (void)geoMessengerDidStart:(id<SLGeoMessenger>)geoMessenger;

/**
 @abstract Called if any error occur during the startup of SLGeoMessenger. The possible error is defined in SLGeoMessengerErrorType.
 
 @discussion If you get SLGeoMessengerErrorTypeLocationManagerNotLoaded you must restart SLGeoMessenger your self. The other error types will trigger a timer and will try again later.
 
 @param geoMessenger The SLGeoMessenger manager object that generated the update event.
 @param error the NSError occured, defined in SLGeoMessengerErrorType
 */
- (void)geoMessenger:(id<SLGeoMessenger>)geoMessenger didFailWithError:(NSError *)error;

/// @name GeoMessenger events

/**
 @abstract Called when a SLGeoMessengerZone is entered.
 
 @param geoMessenger The SLGeoMessenger manager object that generated the update event.
 @param zone The SLGeoMessengerZone entered.
 */
- (void)geoMessenger:(id<SLGeoMessenger>)geoMessenger didEnterZone:(SLGeoMessengerZone *)zone;

/**
 @abstract Called when a SLGeoMessengerZone is left.
 
 @param geoMessenger The SLGeoMessenger manager object that generated the update event.
 @param zone The SLGeoMessengerZone left.
 */
- (void)geoMessenger:(id<SLGeoMessenger>)geoMessenger didLeaveZone:(SLGeoMessengerZone *)zone;

@end
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
