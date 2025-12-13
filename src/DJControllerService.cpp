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

    // If the track is already in cache, we don't need to load it again.
    // CRITICAL: We call .get() not just to retrieve it, but to update its "Last Access Time" (LRU).

    if (cache.contains(title)) {
        cache.get(title); 
        return 1;
    }

    PointerWrapper<AudioTrack> cloned_track = track.clone(); 

    if (cloned_track.get() == nullptr) {
        std::cerr << "[ERROR] Track: \"" << title << "\" failed to clone." << std::endl;
        return 0; 
    }

    cloned_track->load();
    cloned_track->analyze_beatgrid();

    //We use std::move to transfer OWNERSHIP of the new track into the cache.
    // The 'cloned_track' variable becomes empty, and the Cache takes responsibility for deletion.

    bool evicted = cache.put(std::move(cloned_track));

    if (evicted) {
        return -1;
    } else {
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
