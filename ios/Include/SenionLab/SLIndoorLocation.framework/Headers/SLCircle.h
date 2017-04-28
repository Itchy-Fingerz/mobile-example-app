//
//  SLCircle.h
//  SLIndoorLocation
//
<<<<<<< HEAD
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
=======
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
//

#import <Foundation/Foundation.h>
#import "SLGeometryId.h"
#import "SLCoordinate3D.h"

/**
 Class used to define a geofencing area in form of a circle.
 The coordinates that needs to be supplied is marked in the figure below.
 
<<<<<<< HEAD
 ![Image Alt](../../../doc_template/images/circle.jpg)
=======
 ![Image Alt](../img/circle.jpg)
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
 */
@interface SLCircle : NSObject <SLGeometry>

/// @name Initializers

/**
 Constructor for SLCircle.
 
 @param geometryId Id used to identify a geometry, make sure that this is unique to be able identify which region that is detected.
 @param center Center of the circle.
 @param radius Radius of the circle in meters.
 */
- (instancetype)initWithId:(SLGeometryId *)geometryId andCenter:(SLCoordinate3D *)center andRadius:(double)radius;

/// @name Methods

/**
 A hysteresis is used to avoid getting messages about entering/leaving an area to frequently 
 when the user is at the border of the area. The user has to be at the hysteresis distance from 
 the area to be detected as outside. There is a default value in the class, but it can
 be adjusted with this method if necessary.
 
 @param hysteresis distance in meters.
 */
- (void)setHysteresis:(double)hysteresis;

@end
