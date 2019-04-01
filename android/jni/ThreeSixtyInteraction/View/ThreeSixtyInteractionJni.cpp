// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ThreeSixtyInteractionJni.h"
#include "ThreeSixtyInteractionView.h"
#include "AndroidAppThreadAssertionMacros.h"

JNIEXPORT void JNICALL Java_com_eegeo_threesixtyinteractionview_ThreeSixtyInteractionViewJniMethods_CloseButtonClicked(
    JNIEnv* jenv, jobject obj,
    jlong nativeObjectPtr)
{
    ASSERT_UI_THREAD

    ExampleApp::ThreeSixtyInteraction::View::ThreeSixtyInteractionView* pView = reinterpret_cast<ExampleApp::ThreeSixtyInteraction::View::ThreeSixtyInteractionView*>(nativeObjectPtr);
    pView->CloseTapped();
}
