
#pragma once

#include "deebug.hpp"
#include "common.h"

#include <DFPlay.h>


static constexpr uint8_rc MAX_MP3_VOLUME {30};

// there is but one concern
// I've just discovered
// some commands take longer than others
//
// So I have to set unique epsilons/time-blocks
// for some of the remote commands
static constexpr uint16_rc EPS_TRACK_CHANGE   { 400};
static constexpr uint16_rc EPS_PL_CHANGE      {1500};
static constexpr uint16_rc EPS_SHUFFLE_CHANGE {1500};


class Defe {
    public:
        Defe(const uint8_rc, const char**, const uint8_rc*) noexcept;

        void init(Stream&)                  noexcept;
        void startPlaylist(uint8_rc)        noexcept;
        void startAlarm(uint8_rc, uint8_rc) noexcept;
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
        void setVolume(uint8_rc)            noexcept;
        void volumeDown()                   noexcept;
        void volumeUp()                     noexcept;
        void pause()                        noexcept;
        void resume()                       noexcept;
        void stop()                         noexcept;
        void manage()                       noexcept;
        void dumpInfo()                     noexcept;

        uint8_rc getPlaylistIndex()     const noexcept;
        const char* getPlaylistName()         const noexcept;
        const char* getPlaylistName(uint8_rc) const noexcept;
        uint8_rc getTrackNum()          const noexcept;
        uint8_rc getNumTracks()         const noexcept;
        uint8_rc getVolume()            const noexcept;
        uint8_rc getNumPlaylists()      const noexcept;

        uint8_rc isPlaying()     const noexcept;
        uint8_rc isStopped()     const noexcept;
        uint8_rc isOnRepeat()    const noexcept;
        uint8_rc isOnShuffle()   const noexcept;

    private:
        const uint8_rc NUM_PLAYLISTS;
        const char** PLAYLIST_NAMES;
        const uint8_rc* PLAYLIST_LENGTHS;
        Stream* stream;
        DFPlay MP3Player;
        uint8_rc num_folders;
        uint8_rc folder;
        uint8_rc volume;
        uint8_rc track;
        uint8_rc num_tracks;
        uint8_rc* queue;
        char playlist_name[17];
        uint8_rc repeat_p;
        uint8_rc shuffle_p;
        uint8_rc playing_p;
        uint8_rc stopped_p;
        uint8_rc paused_p;
        uint8_rc play_pending_p;
        uint8_rc alarm_sounding_p;

        void make_seq_queue()       noexcept;
        void shuffle_queue()        noexcept;
        void play_df_info_state()   noexcept;
};

