// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "QRScanView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace QRScan
    {
        namespace View
        {
            QRScanView::QRScanView(AndroidNativeState& nativeState)
                : m_nativeState(nativeState)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com/eegeo/qrscanview/QRScanView");
                jclass uiClass = m_nativeState.LoadClass(env, strClassName);
                env->DeleteLocalRef(strClassName);

                m_uiViewClass = static_cast<jclass>(env->NewGlobalRef(uiClass));
                jmethodID uiViewCtor = env->GetMethodID(m_uiViewClass, "<init>", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;J)V");

                jobject instance = env->NewObject(
                                       m_uiViewClass,
                                       uiViewCtor,
                                       m_nativeState.activity,
                                       (jlong)(this)
                                   );

                m_uiView = env->NewGlobalRef(instance);
            }

            QRScanView::~QRScanView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void QRScanView::CloseTapped()
            {
                ASSERT_UI_THREAD
                m_callbacks.ExecuteCallbacks();
            }

            void QRScanView::Open()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID dismissPoiInfo = env->GetMethodID(m_uiViewClass, "openQRScan", "()V");
                env->CallVoidMethod(m_uiView, dismissPoiInfo);
            }

            void QRScanView::Close()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID dismissPoiInfo = env->GetMethodID(m_uiViewClass, "dismissQRScan", "()V");
                env->CallVoidMethod(m_uiView, dismissPoiInfo);
            }

            void QRScanView::SetContent(const std::string& content)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring contentStr = env->NewStringUTF(content.c_str());

                jmethodID displayContentInfo = env->GetMethodID(m_uiViewClass, "displayContent", "(Ljava/lang/String;)V");
                env->CallVoidMethod(m_uiView, displayContentInfo, contentStr);

                env->DeleteLocalRef(contentStr);
            }

            void QRScanView::ShowHiddenText()
            {
                ASSERT_UI_THREAD
                m_hiddenTextCallbacks.ExecuteCallbacks();
            }

            void QRScanView::InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_callbacks.AddCallback(callback);
            }

            void QRScanView::RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback)
            {
                ASSERT_UI_THREAD
                m_callbacks.RemoveCallback(callback);
            }

            void QRScanView::InsertLogoLongPressCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                ASSERT_UI_THREAD
                m_hiddenTextCallbacks.AddCallback(callback);
            }

            void QRScanView::RemoveLogoLongPressCallback(Eegeo::Helpers::ICallback0 &callback)
            {
                ASSERT_UI_THREAD
                m_hiddenTextCallbacks.RemoveCallback(callback);
            }
        }
    }
}
