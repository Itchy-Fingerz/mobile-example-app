if(${ANDROID})
set(headers ${headers} jni/PopUp/View
)
set(currsources
  jni/PopUp/View/PopUpViewModule.cpp  jni/PopUp/View/PopUpView.cpp  jni/PopUp/View/PopUpJni.cpp  jni/PopUp/View/PopUpViewModule.h  jni/PopUp/View/PopUpViewIncludes.h  jni/PopUp/View/PopUpView.h  jni/PopUp/View/PopUpJni.h  jni/PopUp/View/IPopUpViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\PopUp\\View FILES ${currsources})
endif(${ANDROID})
