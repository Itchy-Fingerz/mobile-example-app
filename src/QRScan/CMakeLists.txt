set(headers ${headers} ../src/QRScan
)
set(currsources
  ../src/QRScan/QRScanIndoorPositionTypeMessage.cpp
  ../src/QRScan/QRScanIndoorPositionTypeMessage.h
  ../src/QRScan/QRScanSenionDataMessage.cpp
  ../src/QRScan/QRScanSenionDataMessage.h
  ../src/QRScan/QRScanIndoorAtlasDataMessage.cpp
  ../src/QRScan/QRScanIndoorAtlasDataMessage.h
  ../src/QRScan/QRScanIndoorPositionSettingsMessage.cpp
  ../src/QRScan/QRScanIndoorPositionSettingsMessage.h
  ../src/QRScan/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\QRScan FILES ${currsources})
include(../src/QRScan/SdkModel/CMakeLists.txt)
include(../src/QRScan/View/CMakeLists.txt)
