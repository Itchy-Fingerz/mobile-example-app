//
//  BuildingInfo.h
//  SLIndoorLocation
//
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SLCoordinate3D.h"
#import "SLPixelPoint3D.h"
#import "FloorNr.h"

@class FloorInfo;

/**
 This class keeps information about the building the user is currently in and how the global properties of the building relate to the bitmap such as the long/lat location, orientation and scale.
 
 An example of how a JSON file should look like is available [here](../buildinginfo-json-example.html)
 
 ### Note
 
 The map information in this class is used only for showing the user location on a bitmap image of the building. This class is not used by SLIndoorLocationManager and the navigation filter.
 
 */
@interface BuildingInfo : NSObject

/// @name Initializer

/**
 Init with JSON file.
 
 Store the building properties in a JSON file according to the section "JSON file structure" above. The JSON file is downloaded from Senion Developer Portal.
 
 @param bitmapJsonFilename The json file name.
 */
- (instancetype)initWithBitmapJsonFilename:(NSString *)bitmapJsonFilename;

/**
 Init with JSON NSData.
 
 The data must confirm to the "JSON file structure" above. A JSON file can be downloaded from Senion Developer Portal.
 
 @param bitmapJsonData The json data.
 */
- (instancetype)initWithBitmapJsonData:(NSData *)bitmapJsonData;

/// @name Conversion methods

/**
 This function converts a pixel position to longitude and latitude position. 
 
 @param point The pixel point to convert to location.
 
 @return The pixel point as a location.
 */
- (SLCoordinate3D *)SLPixelPoint3DToSLCoordinate3D:(SLPixelPoint3D *)point;

/**
 Convert a longitude and latitude position to a pixel coordinate.
 
 @param location The location to convert to pixel point.
 
 @return The location as a pixel point.
 */
- (SLPixelPoint3D *)SLCoordinate3DToSLPixelPoint3D:(SLCoordinate3D *)location;

/**
 Convert compass heading to heading relative the image coordinate system.
 
 @param heading The heading to convert.
 @param floorNr The floorNr for the floor to convert the heading to.
 
 @return The heading in the image coordinate system.
 */
- (double)heading2PixelHeading:(double)heading andFloorNr:(FloorNr)floorNr;

/// @name Methods

/**
 Get the FloorInfo for the floorNr.
 
 @param floorNr FloorNr of the requested FloorInfo, nil if it doesn't exist.
 
 @return FloorInfo for floorNr.
 */
- (FloorInfo *)getFloorInfo:(FloorNr)floorNr;

/**
 Get default floorNr.
 
 @return The default floorNr.
 */
- (FloorNr)getDefaultFloorNr;

/**
 Get the number of floors in this building.
 
 @return The total number of floors.
 */
- (NSInteger)getTotalNumberOfFloors;

/// @name Properties

/**
 The name of the building.
 */
@property (readonly, nonatomic, strong) NSMutableString *name;

/**
 The date when the building info file was created.
 */
@property (readonly, nonatomic, strong) NSMutableString *dataDate;

/**
 The dictionary containing the floorInfo of all floors. The key is a NSNumber with the floorNr of that floor.
 */
@property (readonly, nonatomic, strong) NSDictionary *floorInfoList;

/**
 The list containing the floorNr of all floors. This list should be ordered and the first floorNr is the lowest floor in the building.
 */
@property (readonly, nonatomic, strong) NSMutableArray *floorNrArray;
 
@end
