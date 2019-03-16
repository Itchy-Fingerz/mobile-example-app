if(${ANDROID})
set(headers ${headers} jni/PopUp
)
set(currsources
  jni/PopUp/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\PopUp FILES ${currsources})
include(jni/PopUp/View/CMakeLists.txt)
endif(${ANDROID})
