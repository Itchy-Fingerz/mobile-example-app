//
//  SLPath.h
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
 This class represent a path. Currently used for Shortest path.
 */
@interface SLPath : NSObject

/// @name Initializer

/**
 Initializer.
 
 @param pathNodes Coordinates for all nodes on the path.
 @param pathLength The total length of the path.
 @param segmentLengths The length of each segment.
 */
- (instancetype)initWithLocations:(NSArray *)pathNodes
                   andPathLength:(double)pathLength
                andSegmentLengts:(NSArray *)segmentLengths;

/// @name Properties

/**
 @return Coordinates for all nodes on the path.
 */
@property (nonatomic, strong, readonly) NSArray *pathNodes;

/**
 @return The total length of the path.
 */
@property (nonatomic, readonly) double pathLength;

/**
 @return The length of each segment.
 */
@property (nonatomic, strong, readonly) NSArray *segmentLengths;

@end
