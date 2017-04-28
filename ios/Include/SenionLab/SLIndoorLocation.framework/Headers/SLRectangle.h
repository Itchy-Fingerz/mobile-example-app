//
//  SLRectangle.h
//  SLIndoorLocation
//
<<<<<<< HEAD
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
=======
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
//

#import "SLParallelogram.h"

/**
 Class used to define a geofencing area in form of a rectangle.
 The coordinates that needs to be supplied is marked in the figure below.
 
<<<<<<< HEAD
 ![Image Alt](../../../doc_template/images/rectangle.jpg)
=======
 ![Image Alt](../img/rectangle.jpg)
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
 */
@interface SLRectangle : SLParallelogram

/// @name Initializers

/**
 Constructor for SLParallelogram.
 
 @param geometryId Id used to identify a geometry, make sure that this is unique to be able identify which region that is detected.
 @param base Base coordinate of the rectangle.
 @param edge1 The first edge of the rectangle goes from the base to the edge1 coordinate.
 @param edge2 The second edge of the rectangle goes from the base to the edge2 coordinate. To constitute a rectangle rather than a paralellogram, edge2 is projected to be orthogonal to edge1.
 */
- (instancetype)initWithId:(SLGeometryId *)geometryId andBase:(SLCoordinate3D *)base andEdge1:(SLCoordinate3D *)edge1 andEdge2:(SLCoordinate3D *)edge2;

@end
