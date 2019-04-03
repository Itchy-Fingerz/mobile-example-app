if(${ANDROID})
set(headers ${headers} jni/ThreeSixtyInteraction/View
)
set(currsources
  jni/ThreeSixtyInteraction/View/ThreeSixtyInteractionJni.h
  jni/ThreeSixtyInteraction/View/ThreeSixtyInteractionJni.cpp
  jni/ThreeSixtyInteraction/View/ThreeSixtyInteractionView.h
  jni/ThreeSixtyInteraction/View/ThreeSixtyInteractionView.cpp
  jni/ThreeSixtyInteraction/View/ThreeSixtyInteractionViewIncludes.h
  jni/ThreeSixtyInteraction/View/ThreeSixtyInteractionViewModule.h
  jni/ThreeSixtyInteraction/View/ThreeSixtyInteractionViewModule.cpp
  jni/ThreeSixtyInteraction/View/CMakeLists.txt
  jni/ThreeSixtyInteraction/View/IThreeSixtyInteractionViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\ThreeSixtyInteraction\\View FILES ${currsources})
endif(${ANDROID})
