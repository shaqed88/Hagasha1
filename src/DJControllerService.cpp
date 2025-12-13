#include "DJControllerService.h"
#include "MP3Track.h"
#include "WAVTrack.h"
#include <iostream>
#include <memory>

DJControllerService::DJControllerService(size_t cache_size)
    : cache(cache_size) {}
/**
 * TODO: Implement loadTrackToCache method
 */
int DJControllerService::loadTrackToCache(AudioTrack& track) {
    // Your implementation here 
  const std::string title = track.get_title();

    if (cache.contains(title)) {
        cache.get(title); 
        std::cout << "[Controller] HIT: Track '" << title << "' found in cache and access time refreshed." << std::endl;
        return 1;
    }

    //std::cout << "[Controller] MISS: Cloning track '" << title << "' for caching." << std::endl;
    PointerWrapper<AudioTrack> cloned_track = track.clone(); 

    if (cloned_track.get() == nullptr) {
        std::cerr << "[ERROR] Track: \"" << title << "\" failed to clone." << std::endl;
        return 0; 
    }

    //std::cout << "[Controller] Preparing track: load() and analyze_beatgrid()." << std::endl;
    cloned_track->load();
    cloned_track->analyze_beatgrid();

    bool evicted = cache.put(std::move(cloned_track));

    if (evicted) {
        //std::cout << "[Controller] MISS+EVICTION: '" << title << "' loaded, an old track was evicted." << std::endl;
        return -1;
    } else {
        //std::cout << "[Controller] MISS: '" << title << "' loaded successfully." << std::endl;
        return 0;
    }
}

void DJControllerService::set_cache_size(size_t new_size) {
    cache.set_capacity(new_size);
}
//implemented
void DJControllerService::displayCacheStatus() const {
    std::cout << "\n=== Cache Status ===\n";
    cache.displayStatus();
    std::cout << "====================\n";
}

/**
 * TODO: Implement getTrackFromCache method
 */
AudioTrack* DJControllerService::getTrackFromCache(const std::string& track_title) {
    // Your implementation here
    AudioTrack* track = cache.get(track_title);
    if (track != nullptr) {
        return track;
    }
    
    return nullptr; // Placeholder
}
