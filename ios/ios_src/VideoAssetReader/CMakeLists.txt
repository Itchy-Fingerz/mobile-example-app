if(${IOS})
set(headers ${headers} ios_src/VideoAssetReader
)
set(currsources
  ios_src/VideoAssetReader/CMakeLists.txt
  ios_src/VideoAssetReader/VideoAssetReaderModule.h
  ios_src/VideoAssetReader/VideoAssetReaderModule.mm
  ios_src/VideoAssetReader/VideoAssetReaderService.h
  ios_src/VideoAssetReader/VideoAssetReaderService.mm
  ios_src/VideoAssetReader/VideoAssetReaderState.h
  ios_src/VideoAssetReader/VideoAssetReaderState.mm
  ios_src/VideoAssetReader/VideoAssetReaderIncludes.h
  ios_src/VideoAssetReader/AVPlayerStateObserver.h
  ios_src/VideoAssetReader/AVPlayerStateObserver.mm
)
set(sources ${sources} ${currsources})
source_group(\\ios_src\\VideoAssetReader FILES ${currsources})
endif(${IOS})
