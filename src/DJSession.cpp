
#include "DJSession.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <dirent.h>

// ========== CONSTRUCTORS & RULE OF 5 ==========


DJSession::DJSession(const std::string& name, bool play_all)
    : session_name(name),
    library_service(),
    controller_service(),
    mixing_service(),
    config_manager(),
    session_config(),
    track_titles(),
    play_all(play_all),
    stats()
      {
    std::cout << "DJ Session System initialized: " << session_name << std::endl;
}


DJSession::~DJSession() {
    std::cout << "Shutting down DJ Session System: " << session_name << std::endl;
}

// ========== CORE FUNCTIONALITY ==========
bool DJSession::load_playlist(const std::string& playlist_name)  {
    std::cout << "[System] Loading playlist: " << playlist_name << "\n";
    
    // Find the playlist in the session config
    auto it = session_config.playlists.find(playlist_name);
    if (it == session_config.playlists.end()) {
        std::cerr << "[ERROR] Playlist '" << playlist_name << "' not found in configuration.\n";
        return false;
    }
    
    // Load playlist from track indices
    library_service.loadPlaylistFromIndices(playlist_name, it->second);
    
    if (library_service.getPlaylist().is_empty()) {
        return false;
    }
    
    track_titles = library_service.getTrackTitles();
    return true;
}

/**
 * TODO: Implement load_track_to_controller method
 * 
 * REQUIREMENTS:
 * 1. Track Retrieval
 *    - Find track in library using track name
 *    - Handle case when track is not found
 *    - Update error stats if track not found
 * 
 * 2. Controller Loading
 *    - Delegate loading to controller_service
 *    - Pass track by reference to controller
 * 
 * 3. Return Values
 *    1: Cache HIT
 *    0: Cache MISS (or error)
 *   -1: Cache MISS with eviction
 * 
 * @param track_name: Name of track to load
 * @return: Cache operation result code

 */
int DJSession::load_track_to_controller(const std::string& track_name) {
    // Your implementation here
   AudioTrack* canonical_track = library_service.findTrack(track_name);

    if (canonical_track == nullptr) {
        std::cerr << "[ERROR] Track: \"" << track_name << "\" not found in current playlist or library.\n";
        stats.errors++;
        return 0; 
    }

    std::cout << "[System] Loading track '" << track_name << "' to controller....\n";

    int result_code = controller_service.loadTrackToCache(*canonical_track);

    switch (result_code) {
        case 1: 
            stats.cache_hits++;
            break;
        case 0: 
            stats.cache_misses++;
            break;
        case -1: 
            stats.cache_misses++;
            stats.cache_evictions++;
            break;
        default:
            stats.errors++; 
            std::cerr << "[ERROR] Controller loading failed for track '" << track_name << "'.\n";
            break;
    }
    
    return result_code;

}

/**
 * TODO: Implement load_track_to_mixer_deck method
 * 
 * @param track_title: Title of track to load to mixer
 * @return: Whether track was successfully loaded to a deck
 */
bool DJSession::load_track_to_mixer_deck(const std::string& track_title) {
    std::cout << "[System] Delegating track transfer to MixingEngineService for: " << track_title << std::endl;
    // your implementation here
    AudioTrack* track_from_cache = controller_service.getTrackFromCache(track_title);

    if (track_from_cache == nullptr) {
        std::cerr << "[ERROR] Track: \"" << track_title << "\" not found in cache. This should not happen if load_track_to_controller succeeded.\n";
        stats.errors++;
        return false;
    }

    int deck_code = mixing_service.loadTrackToDeck(*track_from_cache);

    
    switch (deck_code) {
        case 0: 
            stats.deck_loads_a++;
            stats.transitions++;
            return true;
        case 1: 
            stats.deck_loads_b++;
            stats.transitions++;
            return true;
        case -1: 
        default:
            std::cerr << "[ERROR] Mixing service failed to load track '" << track_title << "' to deck.\n";
            stats.errors++;
            return false;
    }

}

/**
 * @brief Main simulation loop that orchestrates the DJ performance session.
 * @note Updates session statistics (stats) throughout processing
 * @note Calls print_session_summary() to display results after playlist completion
 */
void DJSession::simulate_dj_performance() {
    std::cout << "=== DJ Controller System ===" << std::endl;
    std::cout << "Starting interactive DJ session..." << std::endl;
    // 1. Load configuration
    if (!load_configuration()) {
        std::cerr << "[ERROR] Failed to load configuration. Aborting session." << std::endl;
        return;
    }
    
    // 2. Build track library from config
    library_service.buildLibrary(session_config.library_tracks);
    
    // 3. Get available playlists from config
    if (session_config.playlists.empty()) {
        std::cerr << "[ERROR] No playlists found in configuration. Aborting session." << std::endl;
        return;
    }
    std::cout << "\nStarting DJ performance simulation..." << std::endl;
    std::cout << "BPM Tolerance: " << session_config.bpm_tolerance << " BPM" << std::endl;
    std::cout << "Auto Sync: " << (session_config.auto_sync ? "enabled" : "disabled") << std::endl;
    std::cout << "Cache Capacity: " << session_config.controller_cache_size << " slots (LRU policy)" << std::endl;
    std::cout << "\n--- Processing Tracks ---" << std::endl;

    std::cout << "TODO: Implement the DJ performance simulation workflow here." << std::endl;
    // Your implementation here
   std::vector<std::string> playlist_names;
    playlist_names.reserve(session_config.playlists.size());

    for (const auto &entry : session_config.playlists) {
        playlist_names.push_back(entry.first);
    }

    std::sort(playlist_names.begin(), playlist_names.end());

    // play_all = true by assignment rules (always automatic mode)
     // bool play_all = true;

    auto process_playlist = [&](const std::string& name) {
        std::cout << "\n=== Loading Playlist: " << name << " ===\n";

        // Load playlist (calls DJLibraryService to deep-clone tracks)
        if (!load_playlist(name)) {
            std::cerr << "[ERROR] Failed to load playlist \"" << name << "\".\n";
            stats.errors++;
            return;
        }

        // Get track titles of the JUST-LOADED playlist
        std::vector<std::string> titles = library_service.getTrackTitles();

        for (const std::string &title : titles) {
            std::cout << "\n-- Processing: " << title << " --\n";
            stats.tracks_processed++;

            // STEP 1: Load into controller LRU cache
            int cache_code = load_track_to_controller(title);

            if (cache_code <= -2) {
                // fatal clone/controller error, do NOT continue to mixer
                continue;
            }

            // STEP 2: Load into mixer decks
            bool deck_ok = load_track_to_mixer_deck(title);

            if (!deck_ok) {
                // mixer logged the error itself
                continue;
            }
        }
    };

    // AUTOMATIC MODE (required by assignment)
    std::cout << "\n[INFO] Running in Automatic Mode (Play All)\n";

    for (const std::string &name : playlist_names) {
        process_playlist(name);
    }

    std::cout << "\n[System] All playlists processed.\n";

    // 7. Print summary
    print_session_summary();
}
 
 



/* 
 * Helper method to load session configuration from file
 * 
 * @return: true if configuration loaded successfully; false on error
 */
bool DJSession::load_configuration() {
    const std::string config_path = "bin/dj_config.txt";
    
    std::cout << "Loading configuration from: " << config_path << std::endl;
    
    if (!SessionFileParser::parse_config_file(config_path, session_config)) {
        std::cerr << "[ERROR] Failed to parse configuration file: " << config_path << std::endl;
        return false;
    }
    
    std::cout << "Configuration loaded successfully." << std::endl;
    std::cout << "BPM Tolerance: " << session_config.bpm_tolerance << " BPM" << std::endl;
    std::cout << "Auto Sync: " << (session_config.auto_sync ? "enabled" : "disabled") << std::endl;
    std::cout << "Cache Size: " << session_config.controller_cache_size << " slots" << std::endl;
    mixing_service.set_auto_sync(session_config.auto_sync);
    mixing_service.set_bpm_tolerance(session_config.bpm_tolerance);
    //update cache size in LRUCache
    controller_service.set_cache_size(session_config.controller_cache_size);
    return true;
}

std::string DJSession::display_playlist_menu_from_config() {
    if (session_config.playlists.empty()) {
        return "";
    }
    
    std::cout << "\n=== Available Playlists ===" << std::endl;
    
    // Build sorted list of playlist names
    std::vector<std::string> playlist_names;
    for (const auto& pair : session_config.playlists) {
        playlist_names.push_back(pair.first);
    }
    std::sort(playlist_names.begin(), playlist_names.end());
    
    // Display numbered list
    for (size_t i = 0; i < playlist_names.size(); ++i) {
        std::cout << (i + 1) << ". " << playlist_names[i] << std::endl;
    }
    std::cout << "0. Cancel" << std::endl;
    
    // Prompt for user selection with validation
    int selection = -1;
    while (true) {
        std::cout << "\nSelect a playlist (1-" << playlist_names.size() << ", 0 to cancel): ";
        std::string input;
        
        if (!std::getline(std::cin, input)) {
            std::cout << "\n[ERROR] Input error. Cancelling session." << std::endl;
            return "";
        }
        
        std::stringstream ss(input);
        if (ss >> selection && ss.eof()) {
            if (selection == 0) {
                return "";
            } else if (selection >= 1 && selection <= static_cast<int>(playlist_names.size())) {
                std::string selected_name = playlist_names[selection - 1];
                std::cout << "Selected: " << selected_name << std::endl;
                return selected_name;
            }
        }
        
        std::cout << "Invalid selection. Please enter a number between 1 and " 
                  << playlist_names.size() << ", or 0 to cancel." << std::endl;
    }
}

void DJSession::print_session_summary() const {
    std::cout << "\n=== DJ Session Summary ===" << std::endl;
    std::cout << "Session: " << session_name << std::endl;
    std::cout << "Tracks processed: " << stats.tracks_processed << std::endl;
    std::cout << "Cache hits: " << stats.cache_hits << std::endl;
    std::cout << "Cache misses: " << stats.cache_misses << std::endl;
    std::cout << "Cache evictions: " << stats.cache_evictions << std::endl;
    std::cout << "Deck A loads: " << stats.deck_loads_a << std::endl;
    std::cout << "Deck B loads: " << stats.deck_loads_b << std::endl;
    std::cout << "Transitions: " << stats.transitions << std::endl;
    std::cout << "Errors: " << stats.errors << std::endl;
    std::cout << "=== Session Complete ===" << std::endl;
}