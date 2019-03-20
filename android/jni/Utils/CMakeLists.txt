if(${ANDROID})
set(headers ${headers} jni/Utils
)
set(currsources
  jni/Utils/AndroidUtils.h  jni/Utils/AndroidUtils.cpp
  jni/Utils/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\Utils FILES ${currsources})
endif(${ANDROID})
