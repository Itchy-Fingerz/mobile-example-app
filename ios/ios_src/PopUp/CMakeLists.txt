if(${IOS})
set(headers ${headers} ios_src/PopUp
)
set(currsources
  ios_src/PopUp/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\PopUp FILES ${currsources})
include(ios_src/PopUp/View/CMakeLists.txt)
endif(${IOS})
