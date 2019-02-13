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

JNIEXPORT void JNICALL Java_com_eegeo_qrscanview_QRScanViewJniMethods_OnQRScan(
        JNIEnv* jenv, jobject obj,
        jlong nativeObjectPtr, jstring host, jdouble latitude, jdouble longitude, jstring buildingId, jdouble orientation)
{
    ASSERT_UI_THREAD

    const char *hName = jenv->GetStringUTFChars(host, 0);
    const char *bId = jenv->GetStringUTFChars(buildingId, 0);

    ExampleApp::QRScan::View::QRScanView* pView = reinterpret_cast<ExampleApp::QRScan::View::QRScanView*>(nativeObjectPtr);
    pView->OnQRScanCompleted(hName, latitude, longitude, bId, orientation);
}
