//
//  SLIndoorLocationEnums.h
//  SLIndoorLocation
//
<<<<<<< HEAD
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
=======
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
//

#import <Foundation/Foundation.h>

#ifndef SLIndoorLocation_SLIndoorLocationEnums_h
#define SLIndoorLocation_SLIndoorLocationEnums_h

<<<<<<< HEAD
/**
 Gives a status of the location estimate.
 */
typedef enum SLLocationStatus : NSInteger SLLocationStatus;
enum SLLocationStatus : NSInteger {
    SLLocationStatusConfirmed,
    SLLocationStatusUnconfirmed,
    SLLocationStatusUnconfirmedWithRadioDisturbances
};

static NSString * const SLLocationStatus_toString[] = {
    [SLLocationStatusConfirmed] = @"CONFIRMED",
    [SLLocationStatusUnconfirmed] = @"UNCONFIRMED",
    [SLLocationStatusUnconfirmedWithRadioDisturbances] = @"UNCONFIRMED_RADIO_DISTURBANCES"
};
=======
#pragma mark - SLIbeaconAuthorizationMethod
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3

/**
 Enum for requesting permission to iBeacon data.
 */
<<<<<<< HEAD
typedef enum SLIbeaconAuthorizationMethod : NSInteger SLIbeaconAuthorizationMethod;
enum SLIbeaconAuthorizationMethod : NSInteger {
    SLRequestAlwaysAuthorization, /**< Requests authorization to monitor iBeacon data in the background. */
    SLRequestWhenInUseAuthorization /**< Requests authorization to monitor iBeacon data only in foreground. */
};

static NSString * const SLIbeaconAuthorizationMethod_toString[] = {
    [SLRequestAlwaysAuthorization] = @"requestAlwaysAuthorization",
    [SLRequestWhenInUseAuthorization] = @"requestWhenInUseAuthorization",
};

typedef enum SLMotionState : NSInteger SLMotionState;
enum SLMotionState : NSInteger {
    SLMotionStateUnknown,
    SLMotionStateStanding,
    SLMotionStateWalking,
    SLMotionStateRunning,
    SLMotionStateStair,
    SLMotionStateEscalator,
    SLMotionStateElevator
};

static NSString * const SLMotionState_toString[] = {
    [SLMotionStateUnknown] = @"Unknown",
    [SLMotionStateStanding] = @"Standing",
    [SLMotionStateWalking] = @"Walking",
    [SLMotionStateRunning] = @"Running",
    [SLMotionStateStair] = @"Stair",
    [SLMotionStateEscalator] = @"Escalator",
    [SLMotionStateElevator] = @"Elevator"
};

=======
typedef NS_ENUM(NSInteger, SLIbeaconAuthorizationMethod) {
    
    /**
     Requests authorization to monitor iBeacon data in the background.
     */
    SLRequestAlwaysAuthorization,
    
    /**
     Requests authorization to monitor iBeacon data only in foreground.
     */
    SLRequestWhenInUseAuthorization
};

#pragma mark - SLMotionState

/**
 Describe the motion state of the device.
 */
typedef NS_ENUM(NSInteger, SLMotionState) {
    
    /**
     The motion state of the device is unknown.
     */
    SLMotionStateUnknown,
    
    /**
     The device is standing still.
     */
    SLMotionStateStanding,
    
    /**
     The device is walking.
     */
    SLMotionStateWalking,
    
    /**
     The device is running.
     */
    SLMotionStateRunning,
    
    /**
     The device is moving up or down a flight of stairs.
     */
    SLMotionStateStair,
    
    /**
     The device is moving up or down an excalator.
     */
    SLMotionStateEscalator,
    
    /**
     The device is moving up or down an elevator.
     */
    SLMotionStateElevator
};

#pragma mark - SLLocationAvailability

/**
 Describe the location availability from ``SLIndoorLocationManager``.
 */
typedef NS_ENUM(NSInteger, SLLocationAvailability) {
    
    /**
     ``SLIndoorLocationManager`` is producing valid locations.
     */
    SLLocationAvailabilityAvailable,
    
    /**
     ``SLIndoorLocationManager`` is unable to produce valid locations
     */
    SLLocationAvailabilityNotAvailable
};

#pragma mark - SLLocationStatus (deprecated)

/**
 @warning The use of this enum have been deprecated and will be removed in a future release of the SDK.
 
 Gives a status of the location estimate.
 */
typedef NS_ENUM(NSInteger, SLLocationStatus) {
    
    /**
     @warning Deprecated!
     */
    SLLocationStatusConfirmed __attribute__((deprecated)),
    
    /**
     @warning Deprecated!
     */
    SLLocationStatusUnconfirmed __attribute__((deprecated)),
    
    /**
     @warning Deprecated!
     */
    SLLocationStatusUnconfirmedWithRadioDisturbances __attribute__((deprecated)),
    
    /**
     @warning Deprecated!
     */
    SLLocationStatusNoLocationAvailable __attribute__((deprecated))
}  __attribute__((deprecated));

>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
#endif
