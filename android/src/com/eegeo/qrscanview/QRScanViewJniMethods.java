// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

package com.eegeo.qrscanview;

public class QRScanViewJniMethods
{
    public static native void CloseButtonClicked(long nativeCallerPointer);
    public static native void LogoLongPress(long nativeCallerPointer);
    public static native void OnQRScan(long nativeCallerPointer, String host, double latitude, double longitude, String buildingId, double orientation);
}
