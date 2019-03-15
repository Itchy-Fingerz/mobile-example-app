set(headers ${headers} ../src/PopUp
)
set(currsources
  ../src/PopUp/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\PopUp FILES ${currsources})
include(../src/PopUp/View/CMakeLists.txt)
