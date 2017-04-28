//
//  BuildingInfo.h
//  SLIndoorLocation
//
<<<<<<< HEAD
//  Copyright (c) 2010-2016, SenionLab AB. All rights reserved.
=======
//  Copyright (c) 2010-2017, Senion AB. All rights reserved.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
//

#import <Foundation/Foundation.h>

#import "SLCoordinate3D.h"
#import "SLPixelPoint3D.h"
#import "FloorNr.h"

@class FloorInfo;

/**
<<<<<<< HEAD
 This class keeps information about the building the user is currently in and how the global
 properties of the building relate to the bitmap such as the long/lat location, orientation and scale.
 
 ## Note
 
 The map information in this class is used only for showing the user location on a bitmap image of the building. This class is not used by SLIndoorLocationManager and the navigation filter.
 
 ## JSON file structure
 
    {
        "mapInfo":{
            "name":"Building name",
            "dataDate":"2016-01-04_08-15-33.401_CET",
            "venueId":"ab3b8b71-cbc5-4d08-b43a-88053232557c",
            "mapId":"c0910068-b3c4-4338-a664-02f52ed90b7c",
            "mapVersionId":"6f8b55b9-0f82-4c33-9a37-9443321c6f31",
            "versionName":"20160104"
        },
        "floors":[
            {
                "floorName":"Floor 1",
                "floorNr":0,
                "bitmapFilename":"image_0.png",
                "bitmapLocation":{"latitude":58.40934413324034,"longitude":15.622574970081972},
                "bitmapOffset":{"x":0.0,"y":0.0},
                "bitmapOrientation":-281.4722357389894,
                "pixelsPerMeter":60.73715860755747,
                "xMaxPixels":1313,
                "yMaxPixels":1248
            }
        ]
    }
=======
 This class keeps information about the building the user is currently in and how the global properties of the building relate to the bitmap such as the long/lat location, orientation and scale.
 
 An example of how a JSON file should look like is available [here](../buildinginfo-json-example.html)
 
 ### Note
 
 The map information in this class is used only for showing the user location on a bitmap image of the building. This class is not used by SLIndoorLocationManager and the navigation filter.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
 
 */
@interface BuildingInfo : NSObject

/// @name Initializer

/**
 Init with JSON file.
 
<<<<<<< HEAD
 Store the building properties in a JSON file according to the section "JSON file structure" above. The JSON file is downloaded from SenionLab Developer Portal.
=======
 Store the building properties in a JSON file according to the section "JSON file structure" above. The JSON file is downloaded from Senion Developer Portal.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
 
 @param bitmapJsonFilename The json file name.
 */
- (instancetype)initWithBitmapJsonFilename:(NSString *)bitmapJsonFilename;

/**
 Init with JSON NSData.
 
<<<<<<< HEAD
 The data must confirm to the "JSON file structure" above. A JSON file can be downloaded from SenionLab Developer Portal.
=======
 The data must confirm to the "JSON file structure" above. A JSON file can be downloaded from Senion Developer Portal.
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
 
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
<<<<<<< HEAD
@property(readonly, nonatomic, strong) NSMutableString *name;
=======
@property (readonly, nonatomic, strong) NSMutableString *name;
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3

/**
 The date when the building info file was created.
 */
<<<<<<< HEAD
@property(readonly, nonatomic, strong) NSMutableString *dataDate;
=======
@property (readonly, nonatomic, strong) NSMutableString *dataDate;
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3

/**
 The dictionary containing the floorInfo of all floors. The key is a NSNumber with the floorNr of that floor.
 */
<<<<<<< HEAD
@property (nonatomic, strong) NSDictionary *floorInfoList;
=======
@property (readonly, nonatomic, strong) NSDictionary *floorInfoList;
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3

/**
 The list containing the floorNr of all floors. This list should be ordered and the first floorNr is the lowest floor in the building.
 */
<<<<<<< HEAD
@property (nonatomic, strong) NSMutableArray *floorNrArray;
=======
@property (readonly, nonatomic, strong) NSMutableArray *floorNrArray;
>>>>>>> 7fa4ef117951caca815b63afd6989315815ae2f3
 
@end
