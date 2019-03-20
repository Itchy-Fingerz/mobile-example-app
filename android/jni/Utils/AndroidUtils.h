// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IUtils.h"
#include "AndroidNativeState.h"

namespace ExampleApp
{
	namespace Utils
	{
		class AndroidUtils : public IUtils
		{
		public:
			AndroidUtils(AndroidNativeState* pNativeState);

			~AndroidUtils();

			void OpenARApplication();

		private:
			AndroidNativeState* m_pNativeState;
			jclass m_utilsClass;
		};
	}
}
