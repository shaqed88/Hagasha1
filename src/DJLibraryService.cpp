#include "DJLibraryService.h"
#include "SessionFileParser.h"
#include "MP3Track.h"
#include "WAVTrack.h"
#include <iostream>
#include <memory>
#include <filesystem>
#include <algorithm> 
#include <vector>


DJLibraryService::DJLibraryService(const Playlist& playlist) 
    : playlist(playlist), library() {}
/**
 * @brief Load a playlist from track indices referencing the library
 * @param library_tracks Vector of track info from config
 */
void DJLibraryService::buildLibrary(const std::vector<SessionConfig::TrackInfo>& library_tracks) {
    //Todo: Implement buildLibrary method
 library.clear(); 

    for (const auto& track_info : library_tracks) {
        AudioTrack* new_track = nullptr;

        if (track_info.type == "MP3") {
            new_track = new MP3Track(
                track_info.title, 
                track_info.artists, 
                track_info.duration_seconds, 
                track_info.bpm, 
                track_info.extra_param1, 
                track_info.extra_param2  !=0           
            );
            std::cout << "MP3Track created: " << track_info.extra_param1 << " kbps\n";
        } else if (track_info.type == "WAV") {
            new_track = new WAVTrack(
                track_info.title, 
                track_info.artists, 
                track_info.duration_seconds, 
                track_info.bpm, 
                track_info.extra_param1, 
                track_info.extra_param2
            );
            std::cout << "WAVTrack created: " 
                      << track_info.extra_param1 << "Hz/" 
                      << track_info.extra_param2 << "bit\n";
        } else {
            std::cerr << "[ERROR] Unknown track format: " << track_info.type << ". Skipping.\n";
            continue;
        }

        if (new_track) {
            library.push_back(PointerWrapper<AudioTrack>(new_track));
        }
    }
    std::cout << "[INFO] Track library built: " << library.size() << " tracks loaded" << std::endl; 
}


/**
 * @brief Display the current state of the DJ library playlist
 * 
 */
void DJLibraryService::displayLibrary() const {
    std::cout << "=== DJ Library Playlist: " 
              << playlist.get_name() << " ===" << std::endl;

    if (playlist.is_empty()) {
        std::cout << "[INFO] Playlist is empty.\n";
        return;
    }

    // Let Playlist handle printing all track info
    playlist.display();

    std::cout << "Total duration: " << playlist.get_total_duration() << " seconds" << std::endl;
}

/**
 * @brief Get a reference to the current playlist
 * 
 * @return Playlist& 
 */
Playlist& DJLibraryService::getPlaylist() {
    // Your implementation here
    return playlist;
}

/**
 * TODO: Implement findTrack method
 * 
 * HINT: Leverage Playlist's find_track method
 */
AudioTrack* DJLibraryService::findTrack(const std::string& track_title) {
    // Your implementation here
AudioTrack* found_track = playlist.find_track(track_title);

    // This is optional logging, but useful for debugging/confirmation
    if (found_track) {
        //std::cout << "[INFO] Found track: '" << track_title << "' in playlist.\n";
    } else {
        //std::cout << "[INFO] Track '" << track_title << "' not found in playlist.\n";
    }

    return found_track;
}
void DJLibraryService::loadPlaylistFromIndices(const std::string& playlist_name, 
                                               const std::vector<int>& track_indices) {
    // Your implementation here
  // (a) Log: [INFO] Loading playlist: <name>
    std::cout << "[INFO] Loading playlist: " << playlist_name << std::endl;

    // (b) Create new Playlist with the given name
    // במקום clear() ו-set_name(), אנחנו יוצרים עצם חדש ודורסים את הישן.
    // אופרטור ההשמה (=) ידאג לשחרר את הזיכרון של הפלייליסט הקודם.
    playlist = Playlist(playlist_name);

    std::cout << "Created playlist: " << playlist_name << std::endl;

    // לולאה על האינדקסים (נשאר אותו דבר)
    for (int index : track_indices) {
        // המרה ל-0-based
        size_t lib_index = index - 1;

        // בדיקת גבולות
        if (index < 1 || lib_index >= library.size()) {
            std::cout << "[WARNING] Invalid track index: " << index << ". Skipping." << std::endl;
            continue;
        }

        // שליפת השיר המקורי
        AudioTrack* canonical_track = library[lib_index].get();
        
        // שכפול (Clone)
        PointerWrapper<AudioTrack> cloned_track = canonical_track->clone();
        
        // בדיקת הצלחה
        if (cloned_track.get() != nullptr) {
            cloned_track->load();
            cloned_track->analyze_beatgrid();
            
            std::string title = cloned_track->get_title();
            
            // הוספה לפלייליסט
            playlist.add_track(cloned_track.release());
            
            std::cout << "Added '" << title << "' to playlist '" << playlist_name << "'" << std::endl;
        } else {
             std::cout << "[ERROR] Failed to clone track at index: " << index << ". Skipping." << std::endl;
        }
    }

    // סיכום
    std::cout << "[INFO] Playlist loaded: " << playlist_name 
              << " (" << playlist.getTracks().size() << " tracks)" << std::endl;
}

/**
 * TODO: Implement getTrackTitles method
 * @return Vector of track titles in the playlist
 */
std::vector<std::string> DJLibraryService::getTrackTitles() const {
    // Your implementation here
 std::vector<std::string> titles;

    std::vector<AudioTrack*> tracks = playlist.getTracks();

    titles.reserve(tracks.size());
    for (AudioTrack* track : tracks) {
        if (track != nullptr) {
            titles.push_back(track->get_title());
        }
    }

    return titles;
}
