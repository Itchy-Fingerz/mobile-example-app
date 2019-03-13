set(headers ${headers} ../src/QRScan
)
set(currsources
  ../src/QRScan/OnOutdoorQRScanCompleteMessage.h  ../src/QRScan/OnOutdoorQRScanCompleteMessage.cpp
  ../src/QRScan/OnIndoorQRScanCompleteMessage.h  ../src/QRScan/OnIndoorQRScanCompleteMessage.cpp
  ../src/QRScan/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\QRScan FILES ${currsources})
include(../src/QRScan/SdkModel/CMakeLists.txt)
include(../src/QRScan/View/CMakeLists.txt)
