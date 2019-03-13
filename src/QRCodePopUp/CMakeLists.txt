set(headers ${headers} ../src/QRCodePopUp
)
set(currsources
  ../src/QRCodePopUp/QRCodePopUpSprite.cpp
  ../src/QRCodePopUp/QRCodePopUpSprite.h
  ../src/QRCodePopUp/CMakeLists.txt

)
set(sources ${sources} ${currsources})
source_group(\\src\\QRCodePopUp FILES ${currsources})
