// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanJni.h"
#include "QRScanView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_qrscanview_QRScanViewJniMethods_CloseButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::QRScan::View::QRScanView* pView = reinterpret_cast<ExampleApp::QRScan::View::QRScanView*>(nativeObjectPtr);
    pView->CloseTapped();
}

JNIEXPORT void JNICALL Java_com_eegeo_qrscanview_QRScanViewJniMethods_OnIndoorQRScan(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr, jdouble latitude, jdouble longitude, jstring buildingId, jint floorIndex, jdouble orientation, jdouble zoomLevel, jdouble tiltAngle)
{
    ASSERT_UI_THREAD

    const char *bId = jenv->GetStringUTFChars(buildingId, 0);
    ExampleApp::QRScan::View::QRScanView* pView = reinterpret_cast<ExampleApp::QRScan::View::QRScanView*>(nativeObjectPtr);
    pView->OnIndoorQRScanCompleted(latitude, longitude, bId, floorIndex, orientation, zoomLevel, tiltAngle);
}

JNIEXPORT void JNICALL Java_com_eegeo_qrscanview_QRScanViewJniMethods_OnOutdoorQRScan(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr, jdouble latitude, jdouble longitude, jdouble orientation, jdouble zoomLevel, jdouble tiltAngle)
{
    ASSERT_UI_THREAD

    ExampleApp::QRScan::View::QRScanView* pView = reinterpret_cast<ExampleApp::QRScan::View::QRScanView*>(nativeObjectPtr);
    pView->OnOutdoorQRScanCompleted(latitude, longitude, orientation, zoomLevel, tiltAngle);
}
