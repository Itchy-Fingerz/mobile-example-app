if(${IOS})
set(headers ${headers} ios_src/AirPortPoiViews
)
set(currsources
  ios_src/AirPortPoiViews/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\AirPortPoiViews FILES ${currsources})
include(ios_src/AirPortPoiViews/View/CMakeLists.txt)
endif(${IOS})
