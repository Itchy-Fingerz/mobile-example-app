//
//  SLPixelPoint2D.h
//  SLIndoorLocation
//
<<<<<<< HEAD
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
=======
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
//

#import <Foundation/Foundation.h>

/**
 This class contains a pixel point.
 */
@interface SLPixelPoint2D : NSObject

/// @name Initializers

/**
 Constructor.
 @param x point in pixels
 @param y point in pixels
 */
- (instancetype)initWithX:(double)x andY:(double)y;

/// @name Properties

/**
 x point in pixels
 */
@property (nonatomic) double x;

/**
 y point in pixels
 */
@property (nonatomic) double y;

@end
