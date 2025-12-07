#include "AudioTrack.h"
#include <iostream>
#include <cstring>
#include <random>
#include <algorithm>
#include <utility>

AudioTrack::AudioTrack(const std::string& title, const std::vector<std::string>& artists, 
                      int duration, int bpm, size_t waveform_samples)
    : title(title), artists(artists), duration_seconds(duration), bpm(bpm), waveform_data(nullptr),
       waveform_size(waveform_samples) {
        std::cout << "AudioTrack created: " << title << " by " << std::endl; 
        if (!artists.empty())
             {
            std::cout << artists[0] << " " << std::endl;
           }

    // Allocate memory for waveform analysis
    waveform_data = new double[waveform_size];

    // Generate some dummy waveform data for testing
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    for (size_t i = 0; i < waveform_size; ++i) {
        waveform_data[i] = dis(gen);
    }
    #ifdef DEBUG
    std::cout << "AudioTrack created: " << title << " by " << std::endl;
    for (const auto& artist : artists) {
        std::cout << artist << " ";
    }
    std::cout << std::endl;
    #endif
}

// ========== TODO: STUDENTS IMPLEMENT RULE OF 5 ==========

AudioTrack::~AudioTrack() {
    // TODO: Implement the destructor
    #ifdef DEBUG
    std::cout << "AudioTrack destructor called for: " << title << std::endl;
    #endif
    // Your code here...
    std::cout << "AudioTrack destructor called for: "
              << title << std::endl;
    delete[] waveform_data; 
    waveform_data = nullptr;
}

AudioTrack::AudioTrack(const AudioTrack& other)

    // TODO: Implement the copy constructor
    #ifdef DEBUG
    std::cout << "AudioTrack copy constructor called for: " << other.title << std::endl;
    #endif
    // Your code here...
     : title(other.title), 
      artists(other.artists),
      duration_seconds(other.duration_seconds), 
      bpm(other.bpm),
      waveform_data(nullptr),
      waveform_size(other.waveform_size)
      
    {
   
    std::cout << "AudioTrack copy constructor called for: " << other.title << std::endl;

     
    if (waveform_size > 0)
         {
        waveform_data = new double[waveform_size];
         
        std::copy(other.waveform_data, other.waveform_data + waveform_size, waveform_data);
        } 
    else 
    {
        waveform_data = nullptr;
    }
   
}

AudioTrack& AudioTrack::operator=(const AudioTrack& other) {
    // TODO: Implement the copy assignment operator
    #ifdef DEBUG
    std::cout << "AudioTrack copy assignment called for: " << other.title << std::endl;
    #endif
    // Your code here...
      if (this == &other) {
        return *this; // מניעת השמה עצמית
    }

    std::cout << "AudioTrack copy assignment called for: " << other.title << std::endl;
    
    double* new_waveform_data = nullptr;
    if (other.waveform_size > 0) {
        new_waveform_data = new double[other.waveform_size]; 
        
        std::copy(other.waveform_data, other.waveform_data + other.waveform_size, new_waveform_data);
    }
    
    if (waveform_data != nullptr) {
        delete[] waveform_data; 
    }
    
    waveform_data = new_waveform_data;
    waveform_size = other.waveform_size;

    
    title= other.title;
    artists = other.artists;
    duration_seconds = other.duration_seconds;
    bpm = other.bpm;
   
    
    return *this;
}
    


AudioTrack::AudioTrack(AudioTrack&& other) noexcept 
    // TODO: Implement the move constructor
    #ifdef DEBUG
    std::cout << "AudioTrack move constructor called for: " << other.title << std::endl;
    #endif
    // Your code here...
    : title(std::move(other.title)),
      artists(std::move(other.artists)),
      duration_seconds(other.duration_seconds),
      bpm(other.bpm),
      waveform_data(other.waveform_data), 
      waveform_size(other.waveform_size)  
      
{
     std::cout << "AudioTrack move constructor called for: " << std::endl;
     
    
    other.waveform_data = nullptr;
    other.waveform_size = 0;
    other.title.clear();
    other.artists.clear(); 
}

AudioTrack& AudioTrack::operator=(AudioTrack&& other) noexcept {
    // TODO: Implement the move assignment operator

    #ifdef DEBUG
    std::cout << "AudioTrack move assignment called for: " << other.title << std::endl;
    #endif
    // Your code here...
    if (this == &other) {
        return *this;
    }
    
    if (waveform_data != nullptr) {
        delete[] waveform_data;
    }
    
    title = std::move(other.title);
    artists = std::move(other.artists);
    duration_seconds = other.duration_seconds;
    bpm = other.bpm;
    waveform_data = other.waveform_data;
    waveform_size = other.waveform_size;

    other.waveform_data = nullptr;
    other.waveform_size = 0;

    other.title.clear();

   
    return *this;
}



void AudioTrack::get_waveform_copy(double* buffer, size_t buffer_size) const {
    if (buffer && waveform_data && buffer_size <= waveform_size) {
        std::memcpy(buffer, waveform_data, buffer_size * sizeof(double));
    }
}