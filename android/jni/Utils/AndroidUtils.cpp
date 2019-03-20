// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidUtils.h"

namespace ExampleApp
{
	namespace Utils
	{
		AndroidUtils::AndroidUtils(AndroidNativeState* pNativeState)
		: m_pNativeState(pNativeState)
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jstring strClassName = env->NewStringUTF("com/eegeo/utils/Utils");
			jclass utilsClass = m_pNativeState->LoadClass(env, strClassName);

			m_utilsClass = static_cast<jclass>(env->NewGlobalRef(utilsClass));

			env->DeleteLocalRef(strClassName);
		}

		AndroidUtils::~AndroidUtils()
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			env->DeleteGlobalRef(m_utilsClass);
		}

		void AndroidUtils::OpenARApplication()
		{
			AndroidSafeNativeThreadAttachment attached(*m_pNativeState);
			JNIEnv* env = attached.envForThread;

			jmethodID beginMethod = env->GetStaticMethodID(m_utilsClass, "openARApplication", "(Lcom/eegeo/entrypointinfrastructure/MainActivity;)V");
			env->CallStaticVoidMethod(m_utilsClass, beginMethod, m_pNativeState->activity);
		}
	}
}
