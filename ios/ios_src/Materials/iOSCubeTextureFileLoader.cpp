// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSCubeTextureFileLoader.h"
#include "Types.h"
#include "Graphics.h"
#include "iOSFileIO.h"
#include "GLState.h"
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFURL.h>
#include <CoreGraphics/CoreGraphics.h>
#include <vector>

namespace
{
    // NOTE: this function is a direct copy from iOSTextureFileLoader; this should be removed if this functionality moves into the platform
    GLenum CalcGLPixelFormat(CGBitmapInfo bitmapInfo, size_t bitsPerPixel)
    {
        GLenum colourFormat;
        
        switch(bitsPerPixel)
        {
            default:
                Eegeo_ASSERT(false && "Unhandled bitsPerPixel");
            case 32:
            {
                switch(bitmapInfo & kCGBitmapAlphaInfoMask)
                {
                    case kCGImageAlphaPremultipliedFirst:
                    case kCGImageAlphaFirst:
                    case kCGImageAlphaNoneSkipFirst:
                        colourFormat = GL_BGRA;
                        Eegeo_ASSERT(false && "GL_BGRA unsupported");
                        break;
                    default:
                        colourFormat = GL_RGBA;
                }
                break;
            }
            case 24:
                colourFormat = GL_RGB;
                break;
            case 16:
                colourFormat = GL_LUMINANCE_ALPHA;
                break;
            case 8:
                colourFormat = GL_LUMINANCE;
                break;
        }
        return colourFormat;
    }
    
    // NOTE: much of the functionality in this function is a direct copy from LoadPNGFromDataProvider in iOSTextureFileLoader; common code should be factored out if this functionality moves into the platform
    void LoadPNGCubeFaceFromDataProvider(GLenum cubeTextureFace, CGDataProviderRef dataProvider, bool invertVertically, int& width, int& height)
    {
        CGImageRef spriteImage = CGImageCreateWithPNGDataProvider((CGDataProviderRef)dataProvider, NULL, FALSE, kCGRenderingIntentDefault);
        width = static_cast<int>(CGImageGetWidth(spriteImage));
        height = static_cast<int>(CGImageGetHeight(spriteImage));
        
        CGBitmapInfo bitmapInfo = CGImageGetBitmapInfo(spriteImage);
        size_t bitsPerPixel = CGImageGetBitsPerPixel(spriteImage);
        size_t bytesPerRow = CGImageGetBytesPerRow(spriteImage);
        
        // iOS only supports premultiplied alpha, cooerce
        // https://developer.apple.com/library/mac/documentation/GraphicsImaging/Conceptual/drawingwithquartz2d/dq_context/dq_context.html#//apple_ref/doc/uid/TP30001066-CH203-BCIBHHBB
        // http://stackoverflow.com/questions/5545600/iphone-cgcontextref-cgbitmapcontextcreate-unsupported-parameter-combination
        CGImageAlphaInfo alphaInfo = CGImageGetAlphaInfo(spriteImage);
        if (alphaInfo == kCGImageAlphaLast)
        {
            alphaInfo = kCGImageAlphaPremultipliedLast;
        }
        else if (alphaInfo == kCGImageAlphaFirst)
        {
            alphaInfo = kCGImageAlphaPremultipliedFirst;
        }
        
        bitmapInfo = bitmapInfo & ~kCGBitmapAlphaInfoMask;
        bitmapInfo |= alphaInfo;
        
        GLubyte* spriteData = (GLubyte *) calloc(height * bytesPerRow, sizeof(GLubyte));
        
        CGColorSpaceRef colorSpace = CGImageGetColorSpace(spriteImage);
        CGContextRef spriteContext = CGBitmapContextCreate(spriteData, width, height, 8, bytesPerRow, colorSpace, bitmapInfo);
        
        if (invertVertically)
        {
            CGContextTranslateCTM(spriteContext, 0, (CGFloat)height);
            CGContextScaleCTM(spriteContext, 1.0, -1.0);
        }
        
        CGContextDrawImage(spriteContext, CGRectMake(0.0, 0.0, (CGFloat)width, (CGFloat)height), spriteImage);
        
        CGImageRelease(spriteImage);
        CGContextRelease(spriteContext);
        
        GLenum colourFormat = CalcGLPixelFormat(bitmapInfo, bitsPerPixel);
        
        Eegeo_GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        Eegeo_GL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        Eegeo_GL(glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        Eegeo_GL(glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        Eegeo_GL(glTexImage2D(cubeTextureFace, 0, colourFormat, width, height, 0, colourFormat, GL_UNSIGNED_BYTE, spriteData));
        
        free(spriteData);
    }
}

namespace ExampleApp
{
    namespace Materials
    {
        namespace iOS
        {
            iOSCubeTextureFileLoader::iOSCubeTextureFileLoader(Eegeo::iOS::iOSFileIO& fileIO)
            :m_fileIO(fileIO)
            {
                
            }

            iOSCubeTextureFileLoader::~iOSCubeTextureFileLoader()
            {
            }
            
            bool iOSCubeTextureFileLoader::LoadPNGCube(Eegeo::Helpers::GLHelpers::TextureInfo& textureInfo, const CubeFaceFileNames& cubeFaceFileNames, bool invertVertically)
            {
                typedef std::pair<std::string, GLenum> CubeMapFaceFileNameMapping;
                
                std::vector<CubeMapFaceFileNameMapping> cubeMapFaceFileNameMappings;
                cubeMapFaceFileNameMappings.push_back(CubeMapFaceFileNameMapping(cubeFaceFileNames.positiveXFileName, GL_TEXTURE_CUBE_MAP_POSITIVE_X));
                cubeMapFaceFileNameMappings.push_back(CubeMapFaceFileNameMapping(cubeFaceFileNames.negativeXFileName, GL_TEXTURE_CUBE_MAP_NEGATIVE_X));
                cubeMapFaceFileNameMappings.push_back(CubeMapFaceFileNameMapping(cubeFaceFileNames.positiveYFileName, GL_TEXTURE_CUBE_MAP_POSITIVE_Y));
                cubeMapFaceFileNameMappings.push_back(CubeMapFaceFileNameMapping(cubeFaceFileNames.negativeYFileName, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y));
                cubeMapFaceFileNameMappings.push_back(CubeMapFaceFileNameMapping(cubeFaceFileNames.positiveZFileName, GL_TEXTURE_CUBE_MAP_POSITIVE_Z));
                cubeMapFaceFileNameMappings.push_back(CubeMapFaceFileNameMapping(cubeFaceFileNames.negativeZFileName, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z));
                
                int width = 0;
                int height = 0;
                
                GLint previousActiveTexture;
                Eegeo_GL(glGetIntegerv(GL_ACTIVE_TEXTURE, &previousActiveTexture));
                
                Eegeo_GL(glGenTextures(1, &textureInfo.textureId));
                
                Eegeo_GL(glActiveTexture(GL_TEXTURE0 + Eegeo::Helpers::GLHelpers::BackgroundThreadSamplerIndex));
                Eegeo_GL(glBindTexture(GL_TEXTURE_CUBE_MAP, textureInfo.textureId));
                
                for(std::vector<CubeMapFaceFileNameMapping>::const_iterator it = cubeMapFaceFileNameMappings.begin(); it != cubeMapFaceFileNameMappings.end(); ++it)
                {
                    char fileURL [512];
                    
                    if(!m_fileIO.GetUrl((*it).first, fileURL))
                    {
                        Eegeo_TTY("FileHandler Error: Could not find file %s\n", (*it).first.c_str());
                        return false;
                    }
                    
                    CGDataProviderRef dataProvider = CGDataProviderCreateWithFilename(fileURL);
                    
                    if (dataProvider)
                    {
                        LoadPNGCubeFaceFromDataProvider((*it).second, dataProvider, invertVertically, width, height);
                        
                        CGDataProviderRelease(dataProvider);
                    }
                    else
                    {
                        Eegeo_GL(glActiveTexture(previousActiveTexture));
                        Eegeo_GL(glDeleteTextures(1, &textureInfo.textureId));
                        
                        textureInfo.textureId = 0;
                        
                        return false;
                    }
                    
                    if(it == cubeMapFaceFileNameMappings.begin())
                    {
                        textureInfo.width = width;
                        textureInfo.height = height;
                    }
                    else
                    {
                        Eegeo_ASSERT(textureInfo.width == width && textureInfo.height == height, "Trying to make cube map with different sized faces");
                    }
                }
                
                Eegeo_GL(glActiveTexture(previousActiveTexture));
                
                return true;
            }
        }
    }
}