set(headers ${headers} ../src/Search/EegeoPoisSetService/SdkModel
)
set(currsources
  ../src/Search/EegeoPoisSetService/SdkModel/CMakeLists.txt
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetJsonParser.cpp
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetJsonParser.h
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetSearchQuery.cpp
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetSearchQuery.h
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetReadableTagMapper.h
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetReadableTagMapper.cpp
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetSearchQueryFactory.cpp
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetSearchQueryFactory.h
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetSearchService.cpp
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetSearchService.h
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetSearchServiceModule.cpp
  ../src/Search/EegeoPoisSetService/SdkModel/EegeoPoiSetSearchServiceModule.h
  ../src/Search/EegeoPoisSetService/SdkModel/IEegeoPoiSetSearchService.h
  ../src/Search/EegeoPoisSetService/SdkModel/IEegeoPoiSetParser.h
  ../src/Search/EegeoPoisSetService/SdkModel/IEegeoPoiSetSearchQuery.h
  ../src/Search/EegeoPoisSetService/SdkModel/IEegeoPoiSetSearchQueryFactory.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\Search\\EegeoPoisSetService\\SdkModel FILES ${currsources})
