if(${ANDROID})
set(headers ${headers} jni/ThreeSixtyInteraction
)
set(currsources
  jni/ThreeSixtyInteraction/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\ThreeSixtyInteraction FILES ${currsources})
include(jni/ThreeSixtyInteraction/View/CMakeLists.txt)
endif(${ANDROID})
