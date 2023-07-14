#!/usr/local/bin/lispscript


(defvar /music-library/     "~/Dropbox/music")
(defvar /playlist-location/ "~/cmus/playlists")
(defvar /sd-location/       "/media/tony/lb-sd-card")

;; TODO: erase?

(defvar /playlists-to-push/ (list
  "A Tribe Called Quest"
  "Architecture in Helsinki"
  "Arcade Fire"
  "Arts and Crafts"
  "Asylum Party"
  "Bachata"
  "Bad Religion"
  "Beach Boys"
  "Beirut"
  "Billy Joel"
  "Bjork"
  "Broken Social Scene"
  "Busta Rhymes"
  "Capos Are Indie"
  "Catalonia Invades"
  "Clash City Rockers"
  "Climatewave and Late Nights"
  "Cocteau Twins"
  "Coldwave"
  "Crack Rock Steady"
  "Crystal Castles"
  "Darkwave"
  "DDT"
  "Dead Can Dance"
  "Dead Prez"
  "Depeche Mode"
  "Disco Flies Bananas"
  "Décima Víctima"
  "Døpe 80s Tracks"
  "Døpe 90s Dance Hits"
  "Echo and The Bunnymen"
  "El Último Vecino"
  "Elliott Smith"
  "Elton John"
  "Elvis Costello"
  "Frank _Just Frank_"
  "Gary Numan"
  "Goth"
  "Greek, Alt NOS"
  "Greek, Folk_Pop NOS"
  "Guided By Voices"
  "Gustavo Cerati"
  "In The Heights"
  "Indie Pop"
  "Interpol"
  "Johnny F----ng Marr"
  "Joy Division"
  "K-The-I"
  "KAITOYΛA"
  "KRS-One"
  "Keane"
  "Ladytron"
  "Little Nemo"
  "Lowlife"
  "MF Doom"
  "Metric"
  "Mitropanos Mania"
  "Morrissey"
  "My Bloody Valentine"
  "NOFX"
  "New Order"
  "Nicki Minaj"
  "Party Jams"
  "Peter Murphy"
  "Peter Tosh"
  "REM"
  "Rakim"
  "Rancid"
  "Reading Time"
  "Ride"
  "Sad Lovers and Giants"
  "Say Hi _To Your Mom_"
  "Shoegaze Space Station"
  "Silvio Rodriguez"
  "Soda Stereo"
  "The Alternative"
  "The Chameleons"
  "The Church"
  "The Coup"
  "The Divine Comedy"
  "The Lawrence Arms"
  "The Left Banke"
  "The Magnetic Fields"
  "The National"
  "The Police"
  "The Psychedelic Furs"
  "The Strokes"
  "They Might Be Giants"
  "Tokyo Police Club"
  "Travlin Music Bustinyaassstyle"
  "U2"
  "Wu-Tang Killa Bees"
  "Young Galaxy"
  "_the beatles"
  "_belle and sebaastian"
  "_the smiths"
  "_cure+radiohead"
  "_pixies_stars_velvet"
  "_sd misc"
))


(defvar /number-of-playlists/ (length /playlists-to-push/))

; (zsh (fn "rm -rf ~A/.Track-1000" /sd-location/) :echo t)
; (terpri)


(defun get-playlist-length (aplaylist)
  (let ((playlist-path (fn •~A/~A• /playlist-location/ aplaylist)))
    (ft "getting playlist length [~A]~%" playlist-path)
    (-<>
      (fn •cat ~A | ack 'mp3$' | wc -l• (escape-namestring/shell playlist-path))
      (zsh <>)
      (parse-integer <>))))


; (for-each /playlists-to-push/
;   (let ((folder-name (fn •~A/~2,'0D• /sd-location/ index!))
;         (playlist-path (fn •~A/~A• /playlist-location/ value!))
;         (playlist-num index!))
;     ; (when (< playlist-num 98) (continue!)) ;; oops
;     (zsh (fn •mkdir -p ~A• folder-name) :echo t)
;     (for-each/line playlist-path
;         (let ((source-name (~r value! "^.+?music" /music-library/))
;               (dest-name (if (<= playlist-num 15)
;                            (fn •~A/~4,'0D.mp3• folder-name index!)
;                            (fn •~A/~3,'0D.mp3• folder-name index!))))
;           (when (> index! 255) (break!))
;           (zsh (fn •cp ~A ~A• (escape-namestring/shell source-name) dest-name)
;                :echo t)))))


(with-a-file "playlist_names.h" :w
  (format stream! "~%#pragma once~%~%")
  (format stream! "constexpr uint8_t NUM_PLAYLISTS {~A}~%~%" /number-of-playlists/)
  (format stream! "const char* playlist_names[] = {~%")
  (for-each /playlists-to-push/
    (let ((cleaned (~ra value! "[^A-Za-z0-9,. -]" "_")))
      (if (> (length value!) 16)
        (format stream! •    "~A..."• (substr cleaned 0 13))
        (format stream! •    "~16:@<~A~>"• cleaned))
      (unless (= index! /number-of-playlists/)
        (format stream! ","))
      (format stream! "~%")))
  (format stream! "};~%~%")

  (format stream! "constexpr uint8_t playlist_lengths[] = {~%")
  (for-each/list /playlists-to-push/
    (let ((realname value!))
      (let ((cleaned (~ra value! "[^A-Za-z0-9,. -]" "_")))
        (format stream! •    ~A• (min (get-playlist-length value!) 255))
        (unless (= index! /number-of-playlists/)
          (format stream! ","))
        (format stream! "~%"))))
  (format stream! "};~%~%"))





