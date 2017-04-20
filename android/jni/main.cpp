// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <jni.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <pthread.h>
#include "AppRunner.h"
#include "main.h"
#include "Logger.h"
#include "AndroidAppThreadAssertions.h"
#include "AndroidImagePathHelpers.h"

using namespace Eegeo::Android;
using namespace Eegeo::Android::Input;

AndroidNativeState g_nativeState;
AppRunner* g_pAppRunner;

namespace
{
    void FillEventFromJniData(
        JNIEnv* jenv,
        jint primaryActionIndex,
        jint primaryActionIdentifier,
        jint numPointers,
        jfloatArray x,
        jfloatArray y,
        jintArray pointerIdentity,
        jintArray pointerIndex,
        TouchInputEvent& event);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* pvt)
{
    ExampleApp::AndroidAppThreadAssertions::NominateCurrentlyRunningThreadAsUiThread();
    g_nativeState.vm = vm;
    return JNI_VERSION_1_6;
}

//lifecycle
JNIEXPORT long JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_createNativeCode(
		JNIEnv* jenv, jobject obj,
		jobject activity,
		jobject assetManager,
		jfloat dpi,
		jint density,
		jstring versionName,
		jint versionCode)
{
    EXAMPLE_LOG("startNativeCode\n");

    ExampleApp::AndroidAppThreadAssertions::NominateCurrentlyRunningThreadAsNativeThread();
    ExampleApp::Helpers::ImageHelpers::SetDeviceDensity(density);

    g_nativeState.javaMainThread = pthread_self();
    g_nativeState.mainThreadEnv = jenv;
    g_nativeState.activity = jenv->NewGlobalRef(activity);
    g_nativeState.activityClass = (jclass)jenv->NewGlobalRef(jenv->FindClass("com/eegeo/entrypointinfrastructure/MainActivity"));
    g_nativeState.deviceDpi = dpi;

    jmethodID getClassLoader = jenv->GetMethodID(g_nativeState.activityClass,"getClassLoader", "()Ljava/lang/ClassLoader;");
    g_nativeState.classLoader = jenv->NewGlobalRef(jenv->CallObjectMethod(activity, getClassLoader));
    g_nativeState.classLoaderClass  = (jclass)jenv->NewGlobalRef(jenv->FindClass("java/lang/ClassLoader"));
    g_nativeState.classLoaderLoadClassMethod = jenv->GetMethodID(g_nativeState.classLoaderClass, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

    g_nativeState.DetermineDeviceModel(jenv);

    jthrowable exc;
    exc = jenv->ExceptionOccurred();

    if (exc)
    {
        jenv->ExceptionDescribe();
        jenv->ExceptionClear();
        return 0;
    }

    g_nativeState.assetManagerGlobalRef = jenv->NewGlobalRef(assetManager);
    g_nativeState.assetManager = AAssetManager_fromJava(jenv, g_nativeState.assetManagerGlobalRef);

    g_nativeState.versionName = jenv->GetStringUTFChars(versionName, 0);
    g_nativeState.versionCode = static_cast<int>(versionCode);

    g_pAppRunner = Eegeo_NEW(AppRunner)(&g_nativeState);

    return ((long)g_pAppRunner);
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_stopUpdatingNativeCode(JNIEnv* jenv, jobject obj)
{
    g_pAppRunner->StopUpdatingNativeBeforeTeardown();
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_destroyNativeCode(JNIEnv* jenv, jobject obj)
{
    EXAMPLE_LOG("stopNativeCode()\n");

    Eegeo_DELETE g_pAppRunner;
    g_pAppRunner = NULL;

    jenv->DeleteGlobalRef(g_nativeState.assetManagerGlobalRef);
    jenv->DeleteGlobalRef(g_nativeState.activity);
    jenv->DeleteGlobalRef(g_nativeState.activityClass);
    jenv->DeleteGlobalRef(g_nativeState.classLoaderClass);
    jenv->DeleteGlobalRef(g_nativeState.classLoader);

    ExampleApp::AndroidAppThreadAssertions::RemoveNominationForNativeThread();
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_pauseNativeCode(JNIEnv* jenv, jobject obj)
{
    g_pAppRunner->Pause();
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_resumeNativeCode(JNIEnv* jenv, jobject obj)
{
    g_pAppRunner->Resume();
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_updateNativeCode(JNIEnv* jenv, jobject obj, jfloat deltaSeconds)
{
    g_pAppRunner->UpdateNative((float)deltaSeconds);
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_updateUiViewCode(JNIEnv* jenv, jobject obj, jfloat deltaSeconds)
{
    g_pAppRunner->UpdateUiViews((float)deltaSeconds);
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_destroyApplicationUi(JNIEnv* jenv, jobject obj)
{
    g_pAppRunner->DestroyApplicationUi();
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_setNativeSurface(JNIEnv* jenv, jobject obj, jobject surface)
{
    if(g_nativeState.window != NULL)
    {
        ANativeWindow_release(g_nativeState.window);
        g_nativeState.window = NULL;
    }

    if (surface != NULL)
    {
        g_nativeState.window = ANativeWindow_fromSurface(jenv, surface);

        if (g_nativeState.window != NULL)
        {
            g_pAppRunner->ActivateSurface();
        }
    }
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_NativeJniCalls_handleUrlOpenEvent(
    JNIEnv* jenv, jobject obj,
	jstring host,
	jstring path)
{
    const char* nativeHost = jenv->GetStringUTFChars(host, JNI_FALSE);
    const char* nativePath = jenv->GetStringUTFChars(path, JNI_FALSE);
    const AppInterface::UrlData data = {nativeHost, nativePath};
    g_pAppRunner->HandleUrlOpenEvent(data);
    jenv->ReleaseStringUTFChars(host, nativeHost);
    jenv->ReleaseStringUTFChars(path, nativePath);
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_EegeoSurfaceView_processNativePointerDown(JNIEnv* jenv, jobject obj,
        jint primaryActionIndex,
        jint primaryActionIdentifier,
        jint numPointers,
        jfloatArray x,
        jfloatArray y,
        jintArray pointerIdentity,
        jintArray pointerIndex)
{
    TouchInputEvent event(false, true, primaryActionIndex, primaryActionIdentifier);
    FillEventFromJniData(jenv, primaryActionIndex, primaryActionIdentifier, numPointers, x, y, pointerIdentity, pointerIndex, event);
    g_pAppRunner->HandleTouchEvent(event);
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_EegeoSurfaceView_processNativePointerUp(JNIEnv* jenv, jobject obj,
        jint primaryActionIndex,
        jint primaryActionIdentifier,
        jint numPointers,
        jfloatArray x,
        jfloatArray y,
        jintArray pointerIdentity,
        jintArray pointerIndex)
{
    TouchInputEvent event(true, false, primaryActionIndex, primaryActionIdentifier);
    FillEventFromJniData(jenv, primaryActionIndex, primaryActionIdentifier, numPointers, x, y, pointerIdentity, pointerIndex, event);
    g_pAppRunner->HandleTouchEvent(event);
}

JNIEXPORT void JNICALL Java_com_eegeo_entrypointinfrastructure_EegeoSurfaceView_processNativePointerMove(JNIEnv* jenv, jobject obj,
        jint primaryActionIndex,
        jint primaryActionIdentifier,
        jint numPointers,
        jfloatArray x,
        jfloatArray y,
        jintArray pointerIdentity,
        jintArray pointerIndex)
{
    TouchInputEvent event(false, false, primaryActionIndex, primaryActionIdentifier);
    FillEventFromJniData(jenv, primaryActionIndex, primaryActionIdentifier, numPointers, x, y, pointerIdentity, pointerIndex, event);
    g_pAppRunner->HandleTouchEvent(event);
}

namespace
{
    void FillEventFromJniData(
        JNIEnv* jenv,
        jint primaryActionIndex,
        jint primaryActionIdentifier,
        jint numPointers,
        jfloatArray x,
        jfloatArray y,
        jintArray pointerIdentity,
        jintArray pointerIndex,
        TouchInputEvent& event)
    {
        jfloat* xBuffer = jenv->GetFloatArrayElements(x, 0);
        jfloat* yBuffer = jenv->GetFloatArrayElements(y, 0);
        jint* identityBuffer = jenv->GetIntArrayElements(pointerIdentity, 0);
        jint* indexBuffer = jenv->GetIntArrayElements(pointerIndex, 0);

        for(int i = 0; i < numPointers; ++ i)
        {
            TouchInputPointerEvent p(xBuffer[i], yBuffer[i], identityBuffer[i], indexBuffer[i]);
            event.pointerEvents.push_back(p);
        }

        jenv->ReleaseFloatArrayElements(x, xBuffer, 0);
        jenv->ReleaseFloatArrayElements(y, yBuffer, 0);
        jenv->ReleaseIntArrayElements(pointerIdentity, identityBuffer, 0);
        jenv->ReleaseIntArrayElements(pointerIndex, indexBuffer, 0);
    }
}
