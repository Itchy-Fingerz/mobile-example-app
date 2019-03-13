set(headers ${headers} ../src/Search/EegeoPoisSetService
)
set(currsources
  ../src/Search/EegeoPoisSetService/CMakeLists.txt
  ../src/Search/EegeoPoisSetService/EegeoPoisSetService.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\EegeoPoisSetService FILES ${currsources})
include(../src/Search/EegeoPoisSetService/SdkModel/CMakeLists.txt)
