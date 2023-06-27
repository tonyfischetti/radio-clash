
#include "ModeMP3.h"


ModeMP3::ModeMP3(Defe& _defe, Sixteen& _sixteen, AudioController& _jefa)
    : defe                  {_defe},
      sixteen               {_sixteen},
      jefa                  {_jefa},
      playlist_select_time  {0} {
}

const char* ModeMP3::getModeName() const {
    return mode_name;
}

const bool ModeMP3::isAudioNeeder() const {
    return true;
}

// ???
void ModeMP3::resume() {
    deebug("mp3 mode", "resuming");
    defe.resume();
}

uint8_t ModeMP3::engage() {
    deebug("mp3 mode", "engaging");
    jefa.turnOnMP3Audio();
    deebug("mp3 mode", "  starting first playlist");
    defe.startPlaylist(1);
    return true;
}

uint8_t ModeMP3::suspend() {
    deebug("mp3 mode", "suspending");
    defe.pause();
    return true;
}

uint8_t ModeMP3::tick() {
    // reset from playlist select mode if it times out
    if (playlist_select_time &&
        (millis() - playlist_select_time) > PLAYLIST_SELECT_TIMEOUT)
        playlist_select_time = 0;
    defe.manage();
    return 0;
}

uint8_t ModeMP3::reCw() {
    deebug("mp3 mode", "rcCw");
    if (playlist_select_time) {
        deebug("mp3 mode", "  while in setting mode");
        // reset time (for timeout)
        playlist_select_time = millis();
        if (playlist_select_index == (defe.getNumPlaylists()-1))
            return true;
        ++playlist_select_index;
    }
    return true;
}

uint8_t ModeMP3::reCcw() {
    deebug("mp3 mode", "rcCcw");
    if (playlist_select_time) {
        deebug("mp3 mode", "  while in setting mode");
        // reset time (for timeout)
        playlist_select_time = millis();
        if (playlist_select_index == 0)
            return true;
        --playlist_select_index;
    }
    return true;
}

uint8_t ModeMP3::rePress() {
    deebug("mp3 mode", "pressed");
    // if not already in playlist select mode
    if (!playlist_select_time) {
        deebug("mp3 mode", "  entering playlist select mode");
        playlist_select_time = millis();
        playlist_select_index = defe.getPlaylistIndex();
    }
    else {
        // choose the current playlist selection index
        deebug("mp3 mode", "  about to leave playlist select mode");
        playlist_select_time = 0;
        defe.startPlaylist(playlist_select_index+1);
    }
    return true;
}

uint8_t ModeMP3::remCircleLeft() {
    deebug("mp3 mode", "going back one playlist?");
    defe.backOnePlaylist();
    return true;
}

uint8_t ModeMP3::remCircleRight() {
    deebug("mp3 mode", "going forward one playlist?");
    defe.forwardOnePlaylist();
    return true;
}

uint8_t ModeMP3::remAsterisk() {
    deebug("mp3 mode", "toggling shuffle?");
    defe.toggleShuffle();
    return true;
}

uint8_t ModeMP3::remRewind() {
    deebug("mp3 mode", "going to previous track?");
    defe.previousTrack();
    return true;
}

uint8_t ModeMP3::remPlayPause() {
    if (defe.isPlaying()) {
        deebug("mp3 mode", "pausing?");
        defe.pause();
    }
    else {
        deebug("mp3 mode", "resuming?");
        defe.resume();
    }
    return true;
}

uint8_t ModeMP3::remFastForward() {
    deebug("mp3 mode", "going to next track?");
    defe.nextTrack();
    return true;
}

uint8_t ModeMP3::remVolumeUp() {
    deebug("mp3 mode", "turning volume up?");
    defe.volumeUp();
    return true;
}

uint8_t ModeMP3::remVolumeDown() {
    deebug("mp3 mode", "turning volume down?");
    defe.volumeDown();
    return true;
}

uint8_t ModeMP3::remNetflix() {
    deebug("mp3 mode", "starting climatewave playlist?");
    defe.startPlaylist(CLIMATEWAVE_PLAYLIST);
    return true;
}

uint8_t ModeMP3::remHulu() {
    deebug("mp3 mode", "starting alternative playlist?");
    defe.startPlaylist(THE_ALTERNATIVE_PLAYLIST);
    return true;
}

uint8_t ModeMP3::display() {
    // if it's not in playlist select mode
    if (!playlist_select_time) {
        snprintf(sixteen.line0, 17, "%s", defe.getPlaylistName());
        snprintf(sixteen.line1, 17, "%d/%d  +%d           ",
                defe.getTrackNum(), defe.getNumTracks(),
                defe.getVolume());
        if (defe.isPlaying())
            sixteen.line1[15] = '>';
        else
            sixteen.line1[15] = '=';
        if (defe.isStopped())
            sixteen.line1[15] = '/';
        if (defe.isOnRepeat())
            sixteen.line1[13] = 'R';
        else
            sixteen.line1[13] = '_';
        if (defe.isOnShuffle())
            sixteen.line1[14] = 'S';
        else
            sixteen.line1[14] = '_';
    }
    else {
        // TODO TODO there should be a better way
        snprintf(sixteen.line0, 17, "Playlist select:              ");
        snprintf(sixteen.line1, 17,
                defe.getPlaylistName(playlist_select_index+1));
    }
    sixteen.update();
    return true;
}

