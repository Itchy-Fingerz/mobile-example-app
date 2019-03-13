// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>

extern "C"
{
    JNIEXPORT void JNICALL Java_com_eegeo_qrscanview_QRScanViewJniMethods_CloseButtonClicked(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr);

    JNIEXPORT void JNICALL Java_com_eegeo_qrscanview_QRScanViewJniMethods_OnIndoorQRScan(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr, jdouble latitude, jdouble longitude, jstring buildingId, jint floorIndex, jdouble orientation, jdouble zoomLevel, jdouble tiltAngle);

    JNIEXPORT void JNICALL Java_com_eegeo_qrscanview_QRScanViewJniMethods_OnOutdoorQRScan(
            JNIEnv* jenv, jobject obj,
            jlong nativeObjectPtr, jdouble latitude, jdouble longitude, jdouble orientation, jdouble zoomLevel, jdouble tiltAngle);
}
