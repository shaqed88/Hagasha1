#include "CacheSlot.h"

CacheSlot::CacheSlot() : 
    track(nullptr), 
    last_access_time(0), 
    occupied(false){
}

void CacheSlot::store(PointerWrapper<AudioTrack> track_ptr, uint64_t access_time) {
    track = std::move(track_ptr);
    last_access_time = access_time;
    occupied = true;
}

AudioTrack* CacheSlot::access(uint64_t access_time) {
    if (!occupied) {
        std::cout << "[CacheSlot DEBUG] Error: Slot accessed but occupied=false!" << std::endl;
        return nullptr;
    }
    
    AudioTrack* ptr = track.get();
    if (ptr == nullptr) {
        std::cout << "[CacheSlot DEBUG] Critical Error: Slot is occupied but internal pointer is NULL!" << std::endl;
    }

    last_access_time = access_time;
    return ptr;
}

void CacheSlot::clear() {
    track.reset(nullptr);
    occupied = false;
    last_access_time = 0;
}