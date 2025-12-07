#include "LRUCache.h"
#include <algorithm>
#include <iostream>
#include <limits>

LRUCache::LRUCache(size_t capacity)
    : slots(capacity), max_size(capacity), access_counter(0) {}

bool LRUCache::contains(const std::string& track_id) const {
    return findSlot(track_id) != max_size;
}

AudioTrack* LRUCache::get(const std::string& track_id) {
size_t index = findSlot(track_id);

    if (index == max_size) {
        std::cout << "[LRUCache] MISS: Track '" << track_id << "' not found in cache." << std::endl;
        return nullptr;
    }

    std::cout << "[LRUCache] HIT: Track '" << track_id << "' served from slot " << index << "." << std::endl;
    return slots[index].access(++access_counter);
}

/**
 * TODO: Implement the put() method for LRUCache
 */
bool LRUCache::put(PointerWrapper<AudioTrack> track) {
 if (track.get() == nullptr) {
        std::cerr << "[LRUCache] Error: Cannot put a null track." << std::endl;
        return false;
    }
    
    const std::string title = track->get_title();
    size_t existing_index = findSlot(title);
    
    if (existing_index != max_size) {
        slots[existing_index].access(++access_counter); 
        std::cout << "[LRUCache] HIT: Track '" << title << "' access refreshed." << std::endl;
        return false; 
    }

    size_t target_slot = findEmptySlot();
    bool evicted = false;
    
    if (target_slot == max_size) {
        evicted = evictLRU();
        
        if (!evicted) {
             std::cerr << "[LRUCache] Error: Cache is full and failed to evict LRU track for '" << title << "'." << std::endl;
             return false;
        }
        
        target_slot = findEmptySlot(); 
        
        if (target_slot == max_size) {
            std::cerr << "[LRUCache] Critical error: Eviction succeeded but still no empty slot." << std::endl;
            return false;
        }
    }
    
    slots[target_slot].store(std::move(track), ++access_counter); 
    
    std::cout << "[LRUCache] MISS: Track '" << title << "' loaded to slot " << target_slot << "." << std::endl;

    return evicted;
}


bool LRUCache::evictLRU() {
size_t index = findLRUSlot();
    
    if (index == max_size) {
        std::cout << "[LRUCache] No occupied slots to evict." << std::endl;
        return false;
    }
    
    AudioTrack* victim = slots[index].getTrack();
    if (victim) {
        std::cout << "[LRUCache] Evicting LRU track: '" << victim-> get_title() << "' from slot " << index << "." << std::endl;
    } else {
        std::cout << "[LRUCache] Evicted slot " << index << " (track pointer was null)." << std::endl;
    }

    slots[index].clear(); 
    return true;
}


size_t LRUCache::size() const {
    size_t count = 0;
    for (const auto& slot : slots) if (slot.isOccupied()) ++count;
    return count;
}

void LRUCache::clear() {
    for (auto& slot : slots) {
        slot.clear();
    }
}

void LRUCache::displayStatus() const {
    std::cout << "[LRUCache] Status: " << size() << "/" << max_size << " slots used\n";
    for (size_t i = 0; i < max_size; ++i) {
        if(slots[i].isOccupied()){
            std::cout << "  Slot " << i << ": " << slots[i].getTrack()->get_title()
                      << " (last access: " << slots[i].getLastAccessTime() << ")\n";
        } else {
            std::cout << "  Slot " << i << ": [EMPTY]\n";
        }
    }
}

size_t LRUCache::findSlot(const std::string& track_id) const {
   for (size_t i = 0; i < max_size; ++i) {
        if (!slots[i].isOccupied()) {
            continue;
        }
        
        AudioTrack* track_ptr = slots[i].getTrack();
        
        if (track_ptr == nullptr) { 
            continue;
        }
        
        if (track_ptr-> get_title() == track_id) {
            return i;
        }
    }
    return max_size;
}

/**
 * TODO: Implement the findLRUSlot() method for LRUCache
 */
size_t LRUCache::findLRUSlot() const {
uint64_t best_time = std::numeric_limits<uint64_t>::max(); 
    size_t best_index = max_size;

    for (size_t i = 0; i < max_size; ++i) {
        if (!slots[i].isOccupied()) {
            continue;
        }
        
        uint64_t t = slots[i].getLastAccessTime();
        
        if (t < best_time) {
            best_time = t;
            best_index = i;
        }
    }
    return best_index;
}

size_t LRUCache::findEmptySlot() const {
    for (size_t i = 0; i < max_size; ++i) {
        if (!slots[i].isOccupied()) return i;
    }
    return max_size;
}

void LRUCache::set_capacity(size_t capacity){
    if (max_size == capacity)
        return;
    //udpate max size
    max_size = capacity;
    //update the slots vector
    slots.resize(capacity);
}