// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.qrscanview;

public class QRScanViewJniMethods
{
    public static native void CloseButtonClicked(long nativeCallerPointer);
    public static native void OnIndoorQRScan(long nativeCallerPointer, double latitude, double longitude, String buildingId, int floorIndex, double orientation, double zoomLevel, double tiltAngle);
    public static native void OnOutdoorQRScan(long nativeCallerPointer, double latitude, double longitude, double orientation, double zoomLevel, double tiltAngle);
}
