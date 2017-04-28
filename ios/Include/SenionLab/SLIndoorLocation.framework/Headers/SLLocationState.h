//
//  SLLocationState.h
//  SLIndoorLocation
//
<<<<<<< HEAD
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
=======
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
//

#import <Foundation/Foundation.h>
#import "SLIndoorLocationEnums.h"

@class SLCoordinate3D;

/**
<<<<<<< HEAD
 THis class represent a location with it's coordinate, uncertaintyRadius and status.
=======
 This class represent a location with it's coordinate and uncertaintyRadius.
 
 @note The use of [SLLocationStatus](../Enums/SLLocationStatus.html) in this class have been deprecated and will be removed in a future release of the SDK.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
 */
@interface SLLocationState : NSObject

/// @name Initializers

/**
<<<<<<< HEAD
 Initialize a SLLocationState
 
 @param location the location
 @param locationUncertaintyRadius the uncertainty radius for the location
 @param locationStatus the status of the location
 */
- (instancetype)initWithLocation:(SLCoordinate3D *)location andLocationUncertainty:(double)locationUncertaintyRadius andLocationStatus:(SLLocationStatus)locationStatus;
=======
Initialize a SLLocationState.

@param location The location.
@param locationUncertaintyRadius The uncertainty radius for the location.
*/
- (instancetype)initWithLocation:(SLCoordinate3D *)location andLocationUncertainty:(double)locationUncertaintyRadius;

/**
 @warning The use of this initializer have been deprecated and will be removed in a future release of the SDK.
 
 Initialize a SLLocationState.
 
 @param location The location.
 @param locationUncertaintyRadius The uncertainty radius for the location.
 @param locationStatus The status of the location.
 */
- (instancetype)initWithLocation:(SLCoordinate3D *)location andLocationUncertainty:(double)locationUncertaintyRadius andLocationStatus:(SLLocationStatus)locationStatus __attribute__((deprecated));
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3

/// @name Properties

/**
<<<<<<< HEAD
 Current location
=======
 Current location.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
 */
@property (nonatomic, strong) SLCoordinate3D* location;

/**
<<<<<<< HEAD
 Current uncertainty in [m]
=======
 Current uncertainty in [m].
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
 */
@property (nonatomic) double locationUncertaintyRadius;

/**
<<<<<<< HEAD
 Current location status.
 */
@property (nonatomic) SLLocationStatus locationStatus;
=======
 NOTE! The use of this property have been deprecated and will be removed in a future release of the SDK.
 
 Current location status.
 */
@property (nonatomic) SLLocationStatus locationStatus __attribute__((deprecated));
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3

@end
