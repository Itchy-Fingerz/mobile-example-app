set(headers ${headers} ../src/QRScanMessageHandler
)
set(currsources
	../src/QRScanMessageHandler/QRScanMessageHandler.h  
	../src/QRScanMessageHandler/QRScanMessageHandler.cpp
	../src/QRScanMessageHandler/CMakeLists.txt
)
set(sources ${sources} ${currsources})
source_group(\\src\\QRScanMessageHandler FILES ${currsources})
