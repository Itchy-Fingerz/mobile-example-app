//
//  SLGeometry.h
//  SLIndoorLocation
//
<<<<<<< HEAD
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
=======
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
//

#import <Foundation/Foundation.h>

@class SLGeometryId;

/**
 Protocol used by all areas that should be monitored in geofencing.
 */
@protocol SLGeometry <NSObject>

/// @name Methods

/**
 @return Get the id for this area.
 */
- (SLGeometryId *)getGeometryId;

@end
