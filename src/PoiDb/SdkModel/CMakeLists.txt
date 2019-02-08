set(headers ${headers} ../src/PoiDb/SdkModel
)
set(currsources
  ../src/PoiDb/SdkModel/PoiDbModule.cpp
  ../src/PoiDb/SdkModel/PoiDbModule.h
  ../src/PoiDb/SdkModel/IPoiDbModule.h
  ../src/PoiDb/SdkModel/PoiDbService.cpp
  ../src/PoiDb/SdkModel/PoiDbService.h
  ../src/PoiDb/SdkModel/IPoiDbService.h
  ../src/PoiDb/SdkModel/IPoiDbLoader.h
  ../src/PoiDb/SdkModel/PoiDbLoader.h
  ../src/PoiDb/SdkModel/PoiDbLoader.cpp
  ../src/PoiDb/SdkModel/PoiDbServiceProvider.cpp
  ../src/PoiDb/SdkModel/PoiDbServiceProvider.h
  ../src/PoiDb/SdkModel/CMakeLists.txt

)
set(sources ${sources} ${currsources})
source_group(\\src\\PoiDb\\SdkModel FILES ${currsources})
