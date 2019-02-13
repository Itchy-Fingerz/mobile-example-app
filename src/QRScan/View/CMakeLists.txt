set(headers ${headers} ../src/QRScan/View
)
set(currsources
  ../src/QRScan/View/QRScan.h
  ../src/QRScan/View/QRScanController.cpp
  ../src/QRScan/View/QRScanController.h
  ../src/QRScan/View/QRScanMenuOption.cpp
  ../src/QRScan/View/QRScanMenuOption.h
  ../src/QRScan/View/QRScanModule.cpp
  ../src/QRScan/View/QRScanModule.h
  ../src/QRScan/View/QRScanOpenableControl.cpp
  ../src/QRScan/View/QRScanOpenableControl.h
  ../src/QRScan/View/QRScanViewModel.cpp
  ../src/QRScan/View/QRScanViewModel.h
  ../src/QRScan/View/CMakeLists.txt
  ../src/QRScan/View/IQRScanModule.h
  ../src/QRScan/View/IQRScanView.h
  ../src/QRScan/View/IQRScanViewModel.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\QRScan\\View FILES ${currsources})
