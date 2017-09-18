if(${IOS})
set(headers ${headers} ios_src/AirPortPoiViews/View
)
set(currsources
  ios_src/AirPortPoiViews/View/CMakeLists.txt
  ios_src/AirPortPoiViews/View/EegeoSearchResultGatePoiView.h
  ios_src/AirPortPoiViews/View/EegeoSearchResultGatePoiView.mm
)

set(resources ${resources}
    ios_src/AirPortPoiViews/View/GatePoiView.xib
    ios_src/AirPortPoiViews/View/GatePoiViewCell.xib
)

set(sources ${sources} ${currsources})
source_group(\\ios_src\\AirPortPoiViews\\View FILES ${currsources})
endif(${IOS})
