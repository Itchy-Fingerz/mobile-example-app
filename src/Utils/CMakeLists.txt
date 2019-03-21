set(headers ${headers} ../src/Utils
)
set(currsources
  ../src/Utils/Utils.h  ../src/Utils/IUtils.h  
  ../src/Utils/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\Utils FILES ${currsources})
