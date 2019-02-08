set(headers ${headers} ../src/Search/EegeoPoisLocalDB/SdkModel
)
set(currsources
  ../src/Search/EegeoPoisLocalDB/SdkModel/CMakeLists.txt
  ../src/Search/EegeoPoisLocalDB/SdkModel/EegeoPoisLocalDBSearchService.cpp
  ../src/Search/EegeoPoisLocalDB/SdkModel/EegeoPoisLocalDBSearchService.h
  ../src/Search/EegeoPoisLocalDB/SdkModel/EegeoPoisLocalDBModule.cpp
  ../src/Search/EegeoPoisLocalDB/SdkModel/EegeoPoisLocalDBModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\EegeoPoisLocalDB\\SdkModel FILES ${currsources})
