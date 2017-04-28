//
//  SLGeofencingListener.h
//  SLIndoorLocation
//
<<<<<<< HEAD
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
=======
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
//

#import <Foundation/Foundation.h>
#import "SLGeometry.h"

/**
<<<<<<< HEAD
 @protocol SLGeofencingDelegate
=======
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
 To receive notifications for geofencing, this protocol must be implemented.
 */
@protocol SLGeofencingDelegate <NSObject>
/**
 Called when an area is entered.
 @param geometry Area that is detected.
 */
- (void) didEnterGeometry:(id<SLGeometry>)geometry;

/**
 Called when an area is left.
 @param geometry Area that is detected.
 */
- (void) didLeaveGeometry:(id<SLGeometry>)geometry;
@end
