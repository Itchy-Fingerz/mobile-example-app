//
//  SLPixelPoint3D.h
//  SLIndoorLocation
//
<<<<<<< HEAD
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
=======
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
//

#import "SLPixelPoint2D.h"
#import "FloorNr.h"

/**
 This class contains a pixel point including a floorNr.
 */
@interface SLPixelPoint3D : SLPixelPoint2D

/// @name Initializers

/**
 Constructor.
 @param x point in pixels
 @param y point in pixels
 @param floorNr of point
 */
- (instancetype)initWithX:(double)x andY:(double)y andFloorNr:(FloorNr)floorNr;

/// @name Properties

/**
 FloorNr
 */
@property (nonatomic) FloorNr floorNr;

@end
