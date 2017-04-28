//
//  SLGeometryId.h
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
 This class is used to identify a geometry that should be monitored. 
 
 Make sure that each geometry has a unique id.
 */
@interface SLGeometryId : NSObject <NSCopying>

/// @name Initializer

/**
 Constructor.
 
 @param geometryId Unique string that identifies your geometry.
 */
- (instancetype)initWithGeometryId:(NSString *)geometryId;

/// @name Properties

/**
 The geometry ID.
 */
@property(strong) NSString *geometryId;

@end
