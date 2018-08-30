set(headers ${headers} ../src/DataSet
)
set(currsources
../src/DataSet/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\DataSet FILES ${currsources})
include(../src/DataSet/SdkModel/CMakeLists.txt)
