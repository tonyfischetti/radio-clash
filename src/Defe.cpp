
#include "Defe.h"


Defe::Defe(const uint8_rc  _num_playlists,
           const char**   _playlist_names,
           const uint8_rc* _playlist_lengths) noexcept
    : NUM_PLAYLISTS     {_num_playlists},
      PLAYLIST_NAMES    {_playlist_names},
      PLAYLIST_LENGTHS  {_playlist_lengths} {
}

void Defe::init(Stream& _stream) noexcept {
    deebug("defe", "calling init()");
    repeat_p = true;
    shuffle_p = false;
    volume = 19;
    folder = 1;
    alarm_sounding_p = false;
    stream  = &_stream;

    // TODO: check for error?
    MP3Player.begin(*stream);

    // We can have a little dynamic memory allocation, as a treat
    // start_playlist always frees this->queue
    deebug("defe", "free heap before malloc: %ld", ESP.getFreeHeap());
    queue = (uint8_rc*) malloc(sizeof(uint8_rc));
    deebug("defe", "after malloc: %ld", ESP.getFreeHeap());
}

void Defe::play_df_info_state() noexcept {
    deebug("defe", "calling play_df_info_state()");
    MP3Player.play(2, folder, queue[track-1], 0, 0);
}

void Defe::make_seq_queue() noexcept {
    deebug("defe", "making sequential queue");
    deebug("defe", "free heap before malloc: %ld", ESP.getFreeHeap());
    queue = (uint8_rc*) malloc(num_tracks * sizeof(uint8_rc));
    deebug("defe", "after malloc: %ld", ESP.getFreeHeap());
    for (uint8_rc i = 0; i < num_tracks; i++) {
        queue[i] = i+1;
    }
}

void Defe::shuffle_queue() noexcept {
    deebug("defe", "shuffling queue");
    /*
     * My name is Tony and I'm here to say:
     * sometimes sequential plays aren't the way.
     * We ain't here to cause no trouble;
     * we're just here to do THE FISCHER-YATES SHUFFLE
     */
    uint8_rc tmp;
    for (uint8_rc i=0; i < (num_tracks-2); i++) {
        uint8_rc rn = random(i, num_tracks);
        tmp = queue[rn];
        queue[rn] = queue[i];
        queue[i] = tmp;
    }
#ifdef DF_DEBUG
    for (uint8_rc i = 0; i < num_tracks; i++) {
        deebug("defe", "    [%d] -> %d", i, queue[i]);
    }
#endif
}

void Defe::startPlaylist(uint8_rc _pl_number) noexcept {
    deebug("defe", "starting playlist: %d", _pl_number);
    free(queue);
    folder = _pl_number;
    track = 1;
    num_tracks = PLAYLIST_LENGTHS[folder-1];
    snprintf(playlist_name, 17, (char*)PLAYLIST_NAMES[folder-1]);
    deebug("defe", "    starting %s", playlist_name);
    make_seq_queue();
    if (shuffle_p)
        shuffle_queue();
    play_pending_p = true;
    play_df_info_state();
}

void Defe::startAlarm(uint8_rc _pl_number, uint8_rc _track_number) noexcept {
    deebug("defe", "starting alarm");
    free(queue);
    folder = _pl_number;
    track = 1;
    deebug("defe", "free heap before malloc: %ld", ESP.getFreeHeap());
    queue = (uint8_rc*) malloc(sizeof(uint8_rc));
    deebug("defe", "after malloc: %ld", ESP.getFreeHeap());
    queue[0] = _track_number;
    num_tracks = 0;
    snprintf(playlist_name, 17, "     <none>          ");
    play_pending_p = true;
    setVolume(100);
    alarm_sounding_p = true;
    play_df_info_state();
}

void Defe::stopAlarm() noexcept {
    stop();
    play_pending_p = true; // >>>
    alarm_sounding_p = false;
}

bool ok_to_change_track_p(bool reset_p=true) noexcept {
    static uint64_rc previous;
    const uint64_rc current {millis()};
    if ((current - previous) > EPS_TRACK_CHANGE) {
        if (reset_p)
            previous = current;
        return true;
    }
    return false;
}

void Defe::previousTrack() noexcept {
    if (!ok_to_change_track_p())
        return;
    deebug("defe", "calling previousTrack()");
    if (track == 1)
        return;
    track -= 1;
    play_pending_p = true;
    play_df_info_state();
}

void Defe::nextTrack() noexcept {
    if (!ok_to_change_track_p())
        return;
    deebug("defe", "calling nextTrack()");
    if (track == num_tracks) {
        if (repeat_p)
            startPlaylist(folder);
        else
            return;
    }
    else {
        if (num_tracks)
            track += 1;
    }
    play_pending_p = true;
    play_df_info_state();
}

bool ok_to_change_playlist_p(bool reset_p=true) noexcept {
    static uint64_rc previous;
    const uint64_rc current = millis();
    if ((current - previous) > EPS_PL_CHANGE) {
        if (reset_p)
            previous = current;
        return true;
    }
    return false;
}

void Defe::backOnePlaylist() noexcept {
    if (!ok_to_change_playlist_p())
        return;
    deebug("defe", "calling backOnePlaylist()");
    if (folder == 1)
        return;
    startPlaylist(folder-1);
}

void Defe::forwardOnePlaylist() noexcept {
    if (!ok_to_change_playlist_p())
        return;
    deebug("defe", "calling forwardOnePlaylist()");
    if (folder == num_folders)
        return;
    startPlaylist(folder+1);
}

void Defe::repeatOff() noexcept {
    if (!ok_to_change_playlist_p())
        return;
    deebug("defe", "turning off repeat");
    repeat_p = false;
    startPlaylist(folder);
}

void Defe::repeatOn() noexcept {
    if (!ok_to_change_playlist_p())
        return;
    deebug("defe", "turning on repeat");
    repeat_p = true;
    startPlaylist(folder);
}

void Defe::toggleRepeat() noexcept {
    if (!ok_to_change_playlist_p())
        return;
    deebug("defe", "toggling repeat");
    repeat_p = !repeat_p;
    startPlaylist(folder);
}

bool ok_to_change_shuffle_p(bool reset_p=true) noexcept {
    static uint64_rc previous;
    const uint64_rc current = millis();
    if (((current - previous) > EPS_SHUFFLE_CHANGE) &&
        ok_to_change_playlist_p(false) &&
        ok_to_change_track_p(false)) {
        if (reset_p)
            previous = current;
        return true;
    }
    return false;
}

void Defe::shuffleOff() noexcept {
    if (!ok_to_change_shuffle_p() || !ok_to_change_playlist_p() ||
        !ok_to_change_track_p())
        return;
    deebug("defe", "turning off shuffle");
    shuffle_p = false;
    startPlaylist(folder);
}

void Defe::shuffleOn() noexcept {
    if (!ok_to_change_shuffle_p())
        return;
    if (!ok_to_change_playlist_p())
        return;
    deebug("defe", "turning on shuffle");
    shuffle_p = true;
    startPlaylist(folder);
}

void Defe::toggleShuffle() noexcept {
    if (!ok_to_change_shuffle_p())
        return;
    deebug("defe", "toggling shuffle");
    shuffle_p = !shuffle_p;
    startPlaylist(folder);
}

void Defe::setVolume(uint8_rc _volume) noexcept {
    if (alarm_sounding_p) {
        deebug("defe", "alarm sounding... rejecting volume change");
        return;
    }
    volume = constrain(_volume, 0, MAX_MP3_VOLUME);
    deebug("defe", "setting volume to %d", volume);
    MP3Player.setVolume(volume);
}

void Defe::volumeDown() noexcept {
    if (volume == 0)
        return;
    volume -= 1;
    deebug("defe", "turning volume down");
    MP3Player.setVolume(volume);
}

void Defe::volumeUp() noexcept {
    if (volume == MAX_MP3_VOLUME)
        return;
    volume += 1;
    deebug("defe", "turning volume up");
    MP3Player.setVolume(volume);
}

void Defe::pause() noexcept {
    deebug("defe", "pausing");
    MP3Player.pause();
}

void Defe::resume() noexcept {
    deebug("defe", "resuming");
    MP3Player.resume();
}

void Defe::stop() noexcept {
    deebug("defe", "stopping");
    MP3Player.stop();
}

void Defe::manage() noexcept {

    if (MP3Player.isPlaying()) {
        playing_p = true;
        stopped_p = false;
        paused_p = false;
        play_pending_p = false;
    }
    else if (MP3Player.isPaused()) {
        playing_p = false;
        stopped_p = false;
        paused_p = true;
    }
    else if (MP3Player.isIdle()) {
        playing_p = false;
        stopped_p = true;
        paused_p = false;
    }

    if (paused_p) {
        if (play_pending_p) {
            resume();
        }
    }

    if (stopped_p) {
        if (!play_pending_p) {
            nextTrack();
        }
    }
    MP3Player.manageDevice();

}

void Defe::dumpInfo() noexcept {
#ifdef DF_DEBUG
    deebug("defe [dump]", "    num folders:   %d", num_folders);
    deebug("defe [dump]", "    folder:        %d", folder);
    deebug("defe [dump]", "    volume:        %d", volume);
    deebug("defe [dump]", "    track:         %d", track);
    deebug("defe [dump]", "    num tracks:    %d", num_tracks);
    deebug("defe [dump]", "    playlist:      %s", playlist_name);
    deebug("defe [dump]", "    repeat?:       %d", repeat_p);
    deebug("defe [dump]", "    shuffle?:      %d", shuffle_p);
    deebug("defe [dump]", "    playing?:      %d", playing_p);
    deebug("defe [dump]", "    stopped?:      %d", stopped_p);
    deebug("defe [dump]", "    paused?:       %d", paused_p);
    deebug("defe [dump]", "    play pending?: %d", play_pending_p);
    deebug("defe [dump]", "  **** info from DFPlay...");
    deebug("defe [dump]", "    ! playing?:    %d", MP3Player.isPlaying());
    deebug("defe [dump]", "    ! paused?:     %d", MP3Player.isPaused());
    deebug("defe [dump]", "    ! idle?:       %d", MP3Player.isIdle());
    deebug("defe [dump]", "    ! failure?:    %d", MP3Player.playFailure());
    deebug("defe [dump]", "    ! repeating?:  %d", MP3Player.isRepeating());
    deebug("defe [dump]", "    ! sleeping?:   %d", MP3Player.isSleeping());
    deebug("defe [dump]", "    ! muted?:      %d", MP3Player.isMuted());
    deebug("defe [dump]", "    ! track num:   %d", MP3Player.getTrackCount());
#else
    (void)0;
#endif
}

const uint8_rc Defe::getPlaylistIndex() const noexcept {
    return folder-1;
}

const char* Defe::getPlaylistName() const noexcept {
    return playlist_name;
}

const char* Defe::getPlaylistName(uint8_rc specific_playlist) const noexcept {
    return (char*)PLAYLIST_NAMES[specific_playlist-1];
}

const uint8_rc Defe::getTrackNum() const noexcept {
    return queue[track-1];
}

const uint8_rc Defe::getNumTracks() const noexcept {
    return num_tracks;
}

const uint8_rc Defe::getVolume() const noexcept {
    return volume;
}

const uint8_rc Defe::getNumPlaylists() const noexcept {
    return NUM_PLAYLISTS;
}

const uint8_rc Defe::isPlaying() const noexcept {
    return playing_p;
}

const uint8_rc Defe::isStopped() const noexcept {
    return stopped_p;
}

const uint8_rc Defe::isOnRepeat() const noexcept {
    return repeat_p;
}

const uint8_rc Defe::isOnShuffle() const noexcept {
    return shuffle_p;
}

