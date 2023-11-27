
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <DFPlay.h>


static constexpr uint8_t MAX_MP3_VOLUME {30};

// there is but one concern
// I've just discovered
// some commands take longer than others
//
// So I have to set unique epsilons/time-blocks
// for some of the remote commands
static constexpr uint16_t EPS_TRACK_CHANGE   { 400};
static constexpr uint16_t EPS_PL_CHANGE      {1500};
static constexpr uint16_t EPS_SHUFFLE_CHANGE {1500};


class Defe {
    public:
        Defe(const uint8_t, const char**, const uint8_t*) noexcept;

        void init(Stream&)                  noexcept;
        void startPlaylist(uint8_t)         noexcept;
        void startAlarm(uint8_t, uint8_t)   noexcept;
        void stopAlarm()                    noexcept;
        void previousTrack()                noexcept;
        void nextTrack()                    noexcept;
        void backOnePlaylist()              noexcept;
        void forwardOnePlaylist()           noexcept;
        void repeatOff()                    noexcept;
        void repeatOn()                     noexcept;
        void toggleRepeat()                 noexcept;
        void shuffleOff()                   noexcept;
        void shuffleOn()                    noexcept;
        void toggleShuffle()                noexcept;
        void setVolume(uint8_t)             noexcept;
        void volumeDown()                   noexcept;
        void volumeUp()                     noexcept;
        void pause()                        noexcept;
        void resume()                       noexcept;
        void stop()                         noexcept;
        void manage()                       noexcept;
        void dumpInfo()                     noexcept;

        const uint8_t getPlaylistIndex()     const noexcept;
        const char* getPlaylistName()        const noexcept;
        const char* getPlaylistName(uint8_t) const noexcept;
        const uint8_t getTrackNum()          const noexcept;
        const uint8_t getNumTracks()         const noexcept;
        const uint8_t getVolume()            const noexcept;
        const uint8_t getNumPlaylists()      const noexcept;

        const uint8_t isPlaying()     const noexcept;
        const uint8_t isStopped()     const noexcept;
        const uint8_t isOnRepeat()    const noexcept;
        const uint8_t isOnShuffle()   const noexcept;

    private:
        const uint8_t NUM_PLAYLISTS;
        const char** PLAYLIST_NAMES;
        const uint8_t* PLAYLIST_LENGTHS;
        Stream* stream;
        DFPlay MP3Player;
        uint8_t num_folders;
        uint8_t folder;
        uint8_t volume;
        uint8_t track;
        uint8_t num_tracks;
        uint8_t* queue;
        char playlist_name[17];
        uint8_t repeat_p;
        uint8_t shuffle_p;
        uint8_t playing_p;
        uint8_t stopped_p;
        uint8_t paused_p;
        uint8_t play_pending_p;
        uint8_t alarm_sounding_p;

        void make_seq_queue()       noexcept;
        void shuffle_queue()        noexcept;
        void play_df_info_state()   noexcept;
};

