set(headers ${headers} ../src/ARMode
)
set(currsources
  ../src/ARMode/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\ARMode FILES ${currsources})
include(../src/ARMode/SdkModel/CMakeLists.txt)
include(../src/ARMode/View/CMakeLists.txt)
