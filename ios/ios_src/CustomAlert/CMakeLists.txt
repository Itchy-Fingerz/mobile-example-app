if(${IOS})
set(headers ${headers} ios_src/CustomAlert
)
set(currsources
  ios_src/CustomAlert/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\CustomAlert FILES ${currsources})
include(ios_src/CustomAlert/View/CMakeLists.txt)
endif(${IOS})
