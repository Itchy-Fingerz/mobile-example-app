set(headers ${headers} ../src/Search/EegeoPoisLocalDB
)
set(currsources
  ../src/Search/EegeoPoisLocalDB/CMakeLists.txt
  ../src/Search/EegeoPoisLocalDB/EegeoPoisLocalDB.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\EegeoPoisLocalDB FILES ${currsources})
include(../src/Search/EegeoPoisLocalDB/SdkModel/CMakeLists.txt)
