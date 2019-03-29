if(${IOS})
set(headers ${headers} ios_src/ThreeSixtyInteraction
)
set(currsources
  ios_src/ThreeSixtyInteraction/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\ThreeSixtyInteraction FILES ${currsources})
include(ios_src/ThreeSixtyInteraction/View/CMakeLists.txt)
endif(${IOS})
