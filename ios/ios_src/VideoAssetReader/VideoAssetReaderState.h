// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include <string>
#include "Types.h"


namespace ExampleApp
{
    namespace VideoAssetReader
    {
        enum PLAYER_STATE:int
        {
            PLAYER_STATE_STOPPED = 0,
            PLAYER_STATE_PLAYING = 1,
            PLAYER_STATE_PAUSED_FOR_BUFFERING = 3,
            PLAYER_STATE_PAUSED_BY_USER = 4,
            PLAYER_STATE_PAUSED_BY_USER_IN_BUFFERING = 5
        };
        
        class VideoAssetReaderState : private Eegeo::NonCopyable
        {
        private:
            
            PLAYER_STATE m_currentPlayerState;
            
        public:
            
            VideoAssetReaderState();
            ~VideoAssetReaderState();
            
            int GetCurrentPlayerState(){return m_currentPlayerState;};
            void SetCurrentPlayerState(PLAYER_STATE playerState) {m_currentPlayerState = playerState;};
        };
    }
}
