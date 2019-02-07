if(${IOS})
set(headers ${headers} ios_src/QRScan/View
)
set(currsources
  ios_src/QRScan/View/QRScanView.h
  ios_src/QRScan/View/QRScanView.mm
  ios_src/QRScan/View/QRScanViewIncludes.h
  ios_src/QRScan/View/QRScanViewInterop.h
  ios_src/QRScan/View/QRScanViewInterop.mm
  ios_src/QRScan/View/QRScanViewModule.h
  ios_src/QRScan/View/QRScanViewModule.mm
  ios_src/QRScan/View/CMakeLists.txt
  ios_src/QRScan/View/IQRScanViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\QRScan\\View FILES ${currsources})
endif(${IOS})
