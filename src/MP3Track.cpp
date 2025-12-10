#include "MP3Track.h"
#include <iostream>
#include <cmath>
#include <algorithm>

MP3Track::MP3Track(const std::string& title, const std::vector<std::string>& artists, 
                   int duration, int bpm, int bitrate, bool has_tags)
    : AudioTrack(title, artists, duration, bpm), bitrate(bitrate), has_id3_tags(has_tags) {

    //std::cout << "MP3Track created: " << bitrate << " kbps" << std::endl;
}

// ========== TODO: STUDENTS IMPLEMENT THESE VIRTUAL FUNCTIONS ==========



MP3Track::~MP3Track() {}

MP3Track::MP3Track(const MP3Track& other)
    : AudioTrack(other), 
      bitrate(other.bitrate),
      has_id3_tags(other.has_id3_tags) 
{}


MP3Track& MP3Track::operator=(const MP3Track& other) {
    if (this != &other) {
        AudioTrack::operator=(other);
        
        bitrate = other.bitrate;
        has_id3_tags = other.has_id3_tags;
    }
    return *this;
}

MP3Track::MP3Track(MP3Track&& other) noexcept 
    : AudioTrack(std::move(other)), 
      bitrate(other.bitrate),
      has_id3_tags(other.has_id3_tags) 
{
}


MP3Track& MP3Track::operator=(MP3Track&& other) noexcept {
    if (this != &other) {
        AudioTrack::operator=(std::move(other));
        
        bitrate = other.bitrate;
        has_id3_tags = other.has_id3_tags;
        
    }
    return *this;
}



void MP3Track::load() {
    std::cout << "[MP3Track::load] Loading MP3: \"" << title
              << "\" at " << bitrate << " kbps..." << std::endl;
    // TODO: Implement MP3 loading with format-specific operations
    // NOTE: Use exactly 2 spaces before the arrow (→) character

    if (has_id3_tags) {
        std::cout << "  → Processing ID3 metadata (artist info, album art, etc.)..." << std::endl;
    } else {
        std::cout << "  → No ID3 tags found." << std::endl;
    }

    std::cout << "  → Decoding MP3 frames..." << std::endl;
    std::cout << "  → Load complete." << std::endl;

    
}

void MP3Track::analyze_beatgrid() {
     std::cout << "[MP3Track::analyze_beatgrid] Analyzing beat grid for: \"" << title << "\"\n";
    // TODO: Implement MP3-specific beat detection analysis
    // NOTE: Use exactly 2 spaces before each arrow (→) character

    double beats = (duration_seconds / 60.0) * bpm;
    int final_beats = static_cast<int>(beats);

    double precision_factor = bitrate / 320.0;

    std::cout << "  → Estimated beats: " << final_beats
              << "  → Compression precision factor: " << precision_factor << std::endl;
}




double MP3Track::get_quality_score() const {
    // TODO: Implement comprehensive quality scoring
    // NOTE: This method does NOT print anything

double score = (bitrate / 320.0) * 100.0;

    if (has_id3_tags) {
        score += 5.0;
    }

    if (bitrate < 128) {
        score -= 10.0;
    }

    if (score > 100.0) score = 100.0;
    if (score < 0.0)   score = 0.0;

    int final_score = static_cast<int>(score);

    std::cout << "Quality: [MP3Track::get_quality_score] \""
              << get_title()
              << "\" score = " << final_score << "/100" << std::endl;

    return score;   
}

PointerWrapper<AudioTrack> MP3Track::clone() const {
    // TODO: Implement polymorphic cloning
return PointerWrapper<AudioTrack>(new MP3Track(*this));
}