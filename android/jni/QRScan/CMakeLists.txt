if(${ANDROID})
set(headers ${headers} jni/QRScan
)
set(currsources
  jni/QRScan/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\jni\\QRScan FILES ${currsources})
include(jni/QRScan/View/CMakeLists.txt)
endif(${ANDROID})
