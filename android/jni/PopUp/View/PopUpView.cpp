// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PopUpView.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace PopUp
    {
        namespace View
        {
            PopUpView::PopUpView(AndroidNativeState& nativeState)
            : m_nativeState(nativeState)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jstring strClassName = env->NewStringUTF("com/eegeo/popupview/PopUpView");
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

            PopUpView::~PopUpView()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;
                jmethodID removeHudMethod = env->GetMethodID(m_uiViewClass, "destroy", "()V");
                env->CallVoidMethod(m_uiView, removeHudMethod);
                env->DeleteGlobalRef(m_uiView);
                env->DeleteGlobalRef(m_uiViewClass);
            }

            void PopUpView::Open(double x, double y)
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID showPopup = env->GetMethodID(m_uiViewClass, "show", "(DD)V");
                env->CallVoidMethod(m_uiView, showPopup, x, y);
            }

            void PopUpView::Close()
            {
                ASSERT_UI_THREAD

                AndroidSafeNativeThreadAttachment attached(m_nativeState);
                JNIEnv* env = attached.envForThread;

                jmethodID hidePopup = env->GetMethodID(m_uiViewClass, "hide", "()V");
                env->CallVoidMethod(m_uiView, hidePopup);
            }
        }
    }
}
