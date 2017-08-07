if(${IOS})
set(headers ${headers} ios_src/AirPortPoiViews/View
)
set(currsources
  ios_src/AirPortPoiViews/View/CMakeLists.txt
  ios_src/AirPortPoiViews/View/EegeoSearchResultSecurityOfficePoiView.h
  ios_src/AirPortPoiViews/View/EegeoSearchResultSecurityOfficePoiView.mm
  ios_src/AirPortPoiViews/View/EegeoSearchResultRatingPoiView.h
  ios_src/AirPortPoiViews/View/EegeoSearchResultRatingPoiView.mm
  ios_src/AirPortPoiViews/View/EegeoSearchResultGatePoiView.h
  ios_src/AirPortPoiViews/View/EegeoSearchResultGatePoiView.mm
  ios_src/AirPortPoiViews/View/EegeoSearchResultFlightTimingTableViewCell.h
  ios_src/AirPortPoiViews/View/EegeoSearchResultFlightTimingTableViewCell.m
  ios_src/AirPortPoiViews/View/EegeoSearchResultCheckInPoiView.h
  ios_src/AirPortPoiViews/View/EegeoSearchResultCheckInPoiView.mm
)

set(resources ${resources}
    ios_src/AirPortPoiViews/View/CouponPoiView.xib
    ios_src/AirPortPoiViews/View/RatingPoiView.xib
    ios_src/AirPortPoiViews/View/SecurityOfficePoiView.xib
    ios_src/AirPortPoiViews/View/GatePoiView.xib
    ios_src/AirPortPoiViews/View/GatePoiViewCell.xib
    ios_src/AirPortPoiViews/View/CheckInPoiView.xib
)

set(sources ${sources} ${currsources})
source_group(\\ios_src\\AirPortPoiViews\\View FILES ${currsources})
endif(${IOS})
