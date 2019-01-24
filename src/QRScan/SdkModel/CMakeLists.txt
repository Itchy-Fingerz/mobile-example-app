set(headers ${headers} ../src/QRScan/SdkModel
)
set(currsources
  ../src/QRScan/SdkModel/QRScanMenuModule.cpp
  ../src/QRScan/SdkModel/QRScanMenuModule.h
  ../src/QRScan/SdkModel/IQRScanMenuModule.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\QRScan\\SdkModel FILES ${currsources})
