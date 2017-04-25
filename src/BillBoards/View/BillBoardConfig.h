// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once


#include <string>
#include <vector>
#include "VectorMath.h"

namespace ExampleApp
{
    namespace BillBoards
    {
        namespace View
        {
            struct BillBoardConfig
            {
                
                int billBoardId;
                std::string poiID;
                std::string textureFilename;
                std::string videoURL;
                int numberOfFrames;
                mutable int currentIndex;
                mutable bool isAnimating;
                mutable bool isPaused;
                std::pair<double, double> originLatLong;
                std::pair<double, double> lineEndTo;
                
                float altitude;
                float boxWidth;
                float boxHeight;
                
                float environmentFlatteningCyclesPerMinute;
                float planeRotation;
                int floorIndex;
                int startDisplayingAtHour;
                int endDisplayingAtHour;
                bool isVideo;
                bool isVideoFrame;
                bool isSpinner;
                bool isPlayBtn;
                bool isSpecialOffer;
                Eegeo::v4 highlightColor;
                
                BillBoardConfig()
                : originLatLong(std::make_pair(0, 0))
                , lineEndTo(std::make_pair(0, 0))
                , altitude(0.f)
                , boxWidth(0.f)
                , boxHeight(0.f)
                , environmentFlatteningCyclesPerMinute(0.f)
                , planeRotation(0.f)
                , floorIndex(0)
                , numberOfFrames(1)
                , currentIndex(0)
                , isAnimating(false)
                , billBoardId(0)
                , startDisplayingAtHour(0)
                , endDisplayingAtHour(0)
                , isVideo(false)
                , isPaused(false)
                , isVideoFrame(false)
                , isSpinner(false)
                , isPlayBtn(false)
                , isSpecialOffer(false)
                , highlightColor(0,0,1,1)
                {
                    
                }
                
                bool IsInStoppedState() const
                {
                    if(!isAnimating && !isPaused)
                    {
                        return true;
                    }
                    
                    return false;
                }
                
                bool IsInPlayingState() const
                {
                    if(isAnimating && !isPaused)
                    {
                        return true;
                    }
                    
                    return false;
                }
                
                bool IsInPausedState() const
                {
                 
                    if(!isAnimating && isPaused)
                    {
                        return true;
                    }
                    
                    return false;
                }
                
                std::string GetNextFrame() const
                {
                    std::string result;
                    
                    if(currentIndex + 1 < numberOfFrames)
                    {
                        currentIndex++;
                    }
                    else
                    {
                        isAnimating = false;
                        currentIndex = 0;
                    }
                    
                    result = "Billboards/" + textureFilename + "_"+ std::to_string(currentIndex) + ".png";
                    return result;
                }
                
                std::string GetInitialFrame() const
                {
                    std::string result;
                    currentIndex = 0;
                    result = "Billboards/" + textureFilename + "_"+ std::to_string(currentIndex) + ".png";
                    return result;
                }            
                
            };
        }
    }
}
