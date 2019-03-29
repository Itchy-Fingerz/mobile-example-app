set(headers ${headers} ../src/AnimatedModels
)
set(currsources
  ../src/AnimatedModels/CMakeLists.txt
  ../src/AnimatedModels/AnimatedModels.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\AnimatedModels FILES ${currsources})
include(../src/AnimatedModels/SdkModel/CMakeLists.txt)
