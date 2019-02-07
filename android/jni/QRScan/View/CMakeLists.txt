if(${ANDROID})
set(headers ${headers} jni/QRScan/View
)
set(currsources
  jni/QRScan/View/QRScanJni.h
  jni/QRScan/View/QRScanJni.cpp
  jni/QRScan/View/QRScanView.h
  jni/QRScan/View/QRScanView.cpp
  jni/QRScan/View/QRScanViewIncludes.h
  jni/QRScan/View/QRScanViewModule.h
  jni/QRScan/View/QRScanViewModule.cpp
  jni/QRScan/View/CMakeLists.txt
  jni/QRScan/View/IQRScanViewModule.h
)
set(sources ${sources} ${currsources})
source_group(\\jni\\QRScan\\View FILES ${currsources})
endif(${ANDROID})
