set(headers ${headers} ../src/ThreeSixtyInteraction
)
set(currsources
  ../src/ThreeSixtyInteraction/CMakeLists.txt
  ../src/ThreeSixtyInteraction/ThreeSixtyInteractionMessage.h
  ../src/ThreeSixtyInteraction/ThreeSixtyInteractionMessage.cpp
)
set(sources ${sources} ${currsources})
source_group(\\src\\ThreeSixtyInteraction FILES ${currsources})
include(../src/ThreeSixtyInteraction/View/CMakeLists.txt)
