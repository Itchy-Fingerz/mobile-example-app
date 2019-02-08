set(headers ${headers} ../src/PoiDb
)
set(currsources
  ../src/PoiDb/PoiDb.h
  ../src/PoiDb/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\PoiDb FILES ${currsources})
include(../src/PoiDb/SdkModel/CMakeLists.txt)
include(../src/PoiDb/Sqlite/CMakeLists.txt)