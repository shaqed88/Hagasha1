#include "MixingEngineService.h"
#include <iostream>
#include <memory>


/**
 * TODO: Implement MixingEngineService constructor
 */
MixingEngineService::MixingEngineService()
    : decks(), active_deck(1), auto_sync(false), bpm_tolerance(0)
{
    
    decks[0] = nullptr;
    decks[1] = nullptr;
    std::cout << "[MixingEngineService] Initialized with 2 empty decks." << std::endl;

}

/**
 * TODO: Implement MixingEngineService destructor
 */
MixingEngineService::~MixingEngineService() {
    // Your implementation here
     std::cout << "[MixingEngineService] Cleaning up decks..." << std::endl;
    for (size_t i = 0; i < 2; ++i) {
        if (decks[i] != nullptr) {
            delete decks[i];
            decks[i] = nullptr;
        }
    }
}



/**
 * TODO: Implement loadTrackToDeck method
 * @param track: Reference to the track to be loaded
 * @return: Index of the deck where track was loaded, or -1 on failure
 */
int MixingEngineService::loadTrackToDeck(const AudioTrack& track) {
    // Your implementation here
 std::cout << "\n=== Loading Track to Deck === " << std::endl;

    PointerWrapper<AudioTrack> new_track_wrapper = track.clone();
    
    if (new_track_wrapper.get() == nullptr) {
        std::cerr << "[ERROR] loadTrackToDeck: Track: '" << track.get_title() << "' failed to clone." << std::endl;
        return -1;
    }
    
    size_t target_deck = 1 - active_deck;
    std::cout << "[Deck Switch] Target deck: " << target_deck << std::endl;

    if (decks[target_deck] != nullptr) {
        delete decks[target_deck];
        decks[target_deck] = nullptr;
    }

    new_track_wrapper->load(); 
    new_track_wrapper->analyze_beatgrid();

    if (auto_sync) {
        if (decks[active_deck] != nullptr) {
            // אם יש שיר בדק הפעיל - מנסים לסנכרן
            if (can_mix_tracks(new_track_wrapper)) {
                sync_bpm(new_track_wrapper);
            }
        } else {
            // אם הדק הפעיל ריק - מדפיסים את השגיאה שהמנחה מצפה לה
            std::cout << "[Sync BPM] Cannot sync - one of the decks is empty." << std::endl;
        }
    }
    
    decks[target_deck] = new_track_wrapper.release(); 
    std::cout << "[Load Complete] '" << decks[target_deck]->get_title() << "' is now loaded on deck " << target_deck << std::endl;

    active_deck = target_deck;
    std::cout << "[Active Deck] Switched to deck " << active_deck << std::endl;

    return target_deck;
}
/**
 * @brief Display current deck status
 */
void MixingEngineService::displayDeckStatus() const {
    std::cout << "\n=== Deck Status ===\n";
    for (size_t i = 0; i < 2; ++i) {
        if (decks[i])
            std::cout << "Deck " << i << ": " << decks[i]->get_title() << "\n";
        else
            std::cout << "Deck " << i << ": [EMPTY]\n";
    }
    std::cout << "Active Deck: " << active_deck << "\n";
    std::cout << "===================\n";
}

/**
 * TODO: Implement can_mix_tracks method
 * 
 * Check if two tracks can be mixed based on BPM difference.
 * 
 * @param track: Track to check for mixing compatibility
 * @return: true if BPM difference <= tolerance, false otherwise
 */
bool MixingEngineService::can_mix_tracks(const PointerWrapper<AudioTrack>& track) const {
    // Your implementation here
    if (decks[active_deck] == nullptr) {
        return false;
    }

    float track_bpm = track->get_bpm();
    float active_bpm = decks[active_deck]->get_bpm();
    
    // חישוב ההפרש
    float diff = std::abs(track_bpm - active_bpm);

    // בדיקה פשוטה ושקטה. בלי cout!
    // שים לב: השימוש ב-<= חשוב (כולל הגבול)
    return (diff <= bpm_tolerance); 

 //AudioTrack* active_track = decks[active_deck];
    //AudioTrack* new_track_ptr = track.get();

    //if (active_track == nullptr || new_track_ptr == nullptr) {
        //return false;
    //}

    //double active_bpm = active_track->get_bpm();
    //double new_bpm = new_track_ptr->get_bpm();
    //double diff = std::abs(active_bpm - new_bpm);

}

/**
 * TODO: Implement sync_bpm method
 * @param track: Track to synchronize with active deck
 */
void MixingEngineService::sync_bpm(const PointerWrapper<AudioTrack>& track) const {
if (decks[active_deck] == nullptr) return;

    float current_bpm = track->get_bpm();
    float target_bpm = decks[active_deck]->get_bpm();

    // רק אם יש הבדל ב-BPM, מבצעים סנכרון ומדפיסים
    // (זה מונע הדפסות סתמיות אם הם כבר זהים)
    if (current_bpm != target_bpm) {
        std::cout << "[Sync BPM] Syncing BPM from " << current_bpm 
                  << " to " << target_bpm << std::endl;
    }

//AudioTrack* active_track = decks[active_deck];
   // AudioTrack* new_track_ptr = track.get();

    //if (active_track == nullptr || new_track_ptr == nullptr) {
      //  return;
   // }

    //float current_bpm = decks[active_deck]->get_bpm();
    //float target_bpm = track->get_bpm();

    //std::cout << "[Sync BPM] Syncing BPM from " << current_bpm << " to " << target_bpm << std::endl;

    //double active_bpm = active_track->get_bpm();
    //double new_bpm = new_track_ptr->get_bpm();
    //double avg_bpm = (active_bpm + new_bpm) / 2.0;

    //std::cout << "[BPM Sync] Syncing BPM of '" << new_track_ptr->get_title() 
              //<< "' from " << new_bpm << " -> " << avg_bpm 
             // << " (Active BPM: " << active_bpm << ")" << std::endl;
              
    
}
