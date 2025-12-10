#include "Playlist.h"
#include "AudioTrack.h"
#include <iostream>
#include <algorithm>
#include <utility>

void swap(Playlist& first, Playlist& second) noexcept {
    using std::swap;
    swap(first.head, second.head);
    swap(first.playlist_name, second.playlist_name);
    swap(first.track_count, second.track_count);
}

Playlist::Playlist(const std::string& name) 
    : head(nullptr), playlist_name(name), track_count(0) {
    
        //std::cout << "Created playlist: " << name << std::endl;
}
// TODO: Fix memory leaks!
// Students must fix this in Phase 1
Playlist::~Playlist() {
    #ifdef DEBUG
    std::cout << "Destroying playlist: " << playlist_name << std::endl;
    #endif
    
     //std::cout << "Destroying playlist: " << playlist_name << std::endl;
   

    PlaylistNode* current = head;
    PlaylistNode* next_node = nullptr;

    while (current != nullptr) {
       next_node = current->next; 

       if (current->track != nullptr) {
        delete current->track; 
     }
     delete current; 
      current = next_node; 

    }
 
     head = nullptr;  
     track_count = 0;

}

void Playlist::add_track(AudioTrack* track) {
    if (!track) {
        std::cout << "[Error] Cannot add null track to playlist" << std::endl;
        
        return;
    }

    // Create new node - this allocates memory!
    PlaylistNode* new_node = new PlaylistNode(track);

    // מקרה 1: הרשימה ריקה - החדש הוא הראש
    if (head == nullptr) {
        head = new_node;
    } 
    // מקרה 2: הרשימה לא ריקה - רצים לסוף ומוסיפים שם
    else {
        PlaylistNode* current = head;
        // לולאה שמוצאת את האיבר האחרון (זה שה-next שלו הוא null)
        while (current->next != nullptr) {
            current = current->next;
        }
        // הדבקת החדש בקצה השרשרת
        current->next = new_node;
    }

    track_count++;
}

void Playlist::remove_track(const std::string& title) {
    PlaylistNode* current = head;
    PlaylistNode* prev = nullptr;

    // Find the track to remove
    while (current && current->track->get_title() != title) {
        prev = current;
        current = current->next;
    }

    if (current) {
        // Remove from linked list
        if (prev) {
            prev->next = current->next;
        } else {
            head = current->next;
        }

        track_count--;
        std::cout << "Removed '" << title << "' from playlist" << std::endl;


        if (current->track != nullptr) {
            delete current->track; 
        }
        
        // B. Delete the dynamically allocated PlaylistNode object
        delete current; 

    } else {
        std::cout << "Track '" << title << "' not found in playlist" << std::endl;
    }
}

void Playlist::display() const {
    std::cout << "\n=== Playlist: " << playlist_name << " ===" << std::endl;
    std::cout << "Track count: " << track_count << std::endl;

    PlaylistNode* current = head;
    int index = 1;

    while (current) {
        std::vector<std::string> artists = current->track->get_artists();
        std::string artist_list;

        std::for_each(artists.begin(), artists.end(), [&](const std::string& artist) {
            if (!artist_list.empty()) {
                artist_list += ", ";
            }
            artist_list += artist;
        });

        AudioTrack* track = current->track;
        std::cout << index << ". " << track->get_title() 
                  << " by " << artist_list
                  << " (" << track->get_duration() << "s, " 
                  << track->get_bpm() << " BPM)" << std::endl;
        current = current->next;
        index++;
    }

    if (track_count == 0) {
        std::cout << "(Empty playlist)" << std::endl;
    }
    std::cout << "========================\n" << std::endl;
}

AudioTrack* Playlist::find_track(const std::string& title) const {
    PlaylistNode* current = head;

    while (current) {
        if (current->track->get_title() == title) {
            return current->track;
        }
        current = current->next;
    }

    return nullptr;
}

int Playlist::get_total_duration() const {
    int total = 0;
    PlaylistNode* current = head;

    while (current) {
        total += current->track->get_duration();
        current = current->next;
    }

    return total;
}

std::vector<AudioTrack*> Playlist::getTracks() const {
    std::vector<AudioTrack*> tracks;
    PlaylistNode* current = head;
    while (current) {
        if (current->track)
            tracks.push_back(current->track);
        current = current->next;
    }
    return tracks;
}

Playlist::Playlist(const Playlist& other)
    : head(nullptr),
      playlist_name(other.playlist_name),
      track_count(0)
{
    PlaylistNode* current_other = other.head;
    PlaylistNode* last_new      = nullptr;

    while (current_other) {
        AudioTrack* cloned_track = nullptr;

        if (current_other->track) {
            PointerWrapper<AudioTrack> cloned_wrapper =
                current_other->track->clone();

            cloned_track = cloned_wrapper.release();
        }

        PlaylistNode* new_node = new PlaylistNode(cloned_track);

        if (!head) {
            head = new_node;
        } else {
            last_new->next = new_node;
        }
        last_new = new_node;

        ++track_count;
        current_other = current_other->next;
    }
}
Playlist& Playlist::operator=(const Playlist& other) {
    Playlist temp(other);
    swap(*this, temp);
    return *this;
}

Playlist::Playlist(Playlist&& other) noexcept 
    : head(other.head), 
      playlist_name(std::move(other.playlist_name)),
      track_count(other.track_count)
{
    other.head         = nullptr;
    other.track_count  = 0;
    other.playlist_name.clear();
}


Playlist& Playlist::operator=(Playlist&& other) noexcept {
    if (this != &other) {
        Playlist temp;       
        swap(*this, temp);   

        head          = other.head;
        playlist_name = std::move(other.playlist_name);
        track_count   = other.track_count;

        other.head        = nullptr;
        other.track_count = 0;
        other.playlist_name.clear();
    }
    return *this;
}