
============= RUNNING INTERACTIVE SOFTWARE =============
Created playlist: 
[MixingEngineService] Initialized with 2 empty decks. Tolerance set to 0 BPM.
DJ Session System initialized: Interactive Session
=== DJ Controller System ===
Starting interactive DJ session...
Loading configuration from: bin/dj_config.txt
Parsed config file: 3 tracks found, 3 playlists found
Configuration loaded successfully.
BPM Tolerance: 10 BPM
Auto Sync: enabled
Cache Size: 3 slots
TODO: Implement DJLibraryService::buildLibrary method
3 tracks to be loaded into library.
AudioTrack created: Silence by 
Delerium 
MP3Track created: 192 kbps
MP3: MP3Track created: 192 kbps
Move constructor called for: 0x5f750f9694c0
AudioTrack created: For An Angel by 
Paul van Dyk 
WAVTrack created: 96000Hz/24bit
WAV: WAVTrack created: 96000Hz/24bit
Move constructor called for: 0x5f750f96bf78
Move constructor called for: 0x5f750f96bf70
AudioTrack created: 9PM (Till I Come) by 
ATB 
MP3Track created: 320 kbps
MP3: MP3Track created: 320 kbps
Move constructor called for: 0x5f750f96b780
Move constructor called for: 0x5f750f96b770
Move constructor called for: 0x5f750f96b778
[INFO] Track library built: 3 tracks loaded.

Starting DJ performance simulation...
BPM Tolerance: 10 BPM
Auto Sync: enabled
Cache Capacity: 3 slots (LRU policy)

--- Processing Tracks ---
TODO: Implement the DJ performance simulation workflow here.

[INFO] Running in Automatic Mode (Play All)

=== Loading Playlist: progressive_house ===
[System] Loading playlist: progressive_house
AudioTrack copy constructor called for: Silence
[MP3Track::load] Loading MP3: "Silence" at 192 kbps...
[MP3Track::load] Loading MP3: "Silence" at 192 kbps...
  → Processing ID3 metadata (artist info, album art, etc.)...
  → Decoding MP3 frames...
  → Load complete.
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "Silence"
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "Silence"
  → Estimated beats: 840  → Compression precision factor: 0.6
Added 'Silence' to playlist ''
AudioTrack copy constructor called for: For An Angel
[WAVTrack::load] Loading WAV: "For An Angel" at 96000Hz/24bit (uncompressed)...
  → Estimated file size: 241920000 bytes
  → Fast loading due to uncompressed format.
[WAVTrack::analyze_beatgrid] Analyzing beat grid for: "For An Angel"
[WAVTrack::analyze_beatgrid] Analyzing beat grid for: "For An Angel"
  → Estimated beats: 945  → Precision factor: 1 (uncompressed audio)
Added 'For An Angel' to playlist ''
AudioTrack copy constructor called for: 9PM (Till I Come)
[MP3Track::load] Loading MP3: "9PM (Till I Come)" at 320 kbps...
[MP3Track::load] Loading MP3: "9PM (Till I Come)" at 320 kbps...
  → Processing ID3 metadata (artist info, album art, etc.)...
  → Decoding MP3 frames...
  → Load complete.
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "9PM (Till I Come)"
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "9PM (Till I Come)"
  → Estimated beats: 750  → Compression precision factor: 1
Added '9PM (Till I Come)' to playlist ''

-- Processing: 9PM (Till I Come) --
[INFO] Found track: '9PM (Till I Come)' in playlist.
[System] Loading track '9PM (Till I Come)' to controller....
[Controller] MISS: Cloning track '9PM (Till I Come)' for caching.
AudioTrack copy constructor called for: 9PM (Till I Come)
[Controller] Preparing track: load() and analyze_beatgrid().
[MP3Track::load] Loading MP3: "9PM (Till I Come)" at 320 kbps...
[MP3Track::load] Loading MP3: "9PM (Till I Come)" at 320 kbps...
  → Processing ID3 metadata (artist info, album art, etc.)...
  → Decoding MP3 frames...
  → Load complete.
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "9PM (Till I Come)"
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "9PM (Till I Come)"
  → Estimated beats: 750  → Compression precision factor: 1
Move constructor called for: 0x7ffde5ecc308
Move constructor called for: 0x7ffde5ecc278
[LRUCache] MISS: Track '9PM (Till I Come)' loaded to slot 0.
[Controller] MISS: '9PM (Till I Come)' loaded successfully.
[System] Delegating track transfer to MixingEngineService for: 9PM (Till I Come)

-- Processing: For An Angel --
[INFO] Found track: 'For An Angel' in playlist.
[System] Loading track 'For An Angel' to controller....
[Controller] MISS: Cloning track 'For An Angel' for caching.
AudioTrack copy constructor called for: For An Angel
[Controller] Preparing track: load() and analyze_beatgrid().
[WAVTrack::load] Loading WAV: "For An Angel" at 96000Hz/24bit (uncompressed)...
  → Estimated file size: 241920000 bytes
  → Fast loading due to uncompressed format.
[WAVTrack::analyze_beatgrid] Analyzing beat grid for: "For An Angel"
[WAVTrack::analyze_beatgrid] Analyzing beat grid for: "For An Angel"
  → Estimated beats: 945  → Precision factor: 1 (uncompressed audio)
Move constructor called for: 0x7ffde5ecc308
Move constructor called for: 0x7ffde5ecc278
[LRUCache] MISS: Track 'For An Angel' loaded to slot 1.
[Controller] MISS: 'For An Angel' loaded successfully.
[System] Delegating track transfer to MixingEngineService for: For An Angel

-- Processing: Silence --
[INFO] Found track: 'Silence' in playlist.
[System] Loading track 'Silence' to controller....
[Controller] MISS: Cloning track 'Silence' for caching.
AudioTrack copy constructor called for: Silence
[Controller] Preparing track: load() and analyze_beatgrid().
[MP3Track::load] Loading MP3: "Silence" at 192 kbps...
[MP3Track::load] Loading MP3: "Silence" at 192 kbps...
  → Processing ID3 metadata (artist info, album art, etc.)...
  → Decoding MP3 frames...
  → Load complete.
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "Silence"
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "Silence"
  → Estimated beats: 840  → Compression precision factor: 0.6
Move constructor called for: 0x7ffde5ecc308
Move constructor called for: 0x7ffde5ecc278
[LRUCache] MISS: Track 'Silence' loaded to slot 2.
[Controller] MISS: 'Silence' loaded successfully.
[System] Delegating track transfer to MixingEngineService for: Silence

=== Loading Playlist: test_playlist ===
[System] Loading playlist: test_playlist
AudioTrack copy constructor called for: Silence
[MP3Track::load] Loading MP3: "Silence" at 192 kbps...
[MP3Track::load] Loading MP3: "Silence" at 192 kbps...
  → Processing ID3 metadata (artist info, album art, etc.)...
  → Decoding MP3 frames...
  → Load complete.
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "Silence"
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "Silence"
  → Estimated beats: 840  → Compression precision factor: 0.6
Added 'Silence' to playlist ''
AudioTrack copy constructor called for: For An Angel
[WAVTrack::load] Loading WAV: "For An Angel" at 96000Hz/24bit (uncompressed)...
  → Estimated file size: 241920000 bytes
  → Fast loading due to uncompressed format.
[WAVTrack::analyze_beatgrid] Analyzing beat grid for: "For An Angel"
[WAVTrack::analyze_beatgrid] Analyzing beat grid for: "For An Angel"
  → Estimated beats: 945  → Precision factor: 1 (uncompressed audio)
Added 'For An Angel' to playlist ''
AudioTrack copy constructor called for: 9PM (Till I Come)
[MP3Track::load] Loading MP3: "9PM (Till I Come)" at 320 kbps...
[MP3Track::load] Loading MP3: "9PM (Till I Come)" at 320 kbps...
  → Processing ID3 metadata (artist info, album art, etc.)...
  → Decoding MP3 frames...
  → Load complete.
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "9PM (Till I Come)"
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "9PM (Till I Come)"
  → Estimated beats: 750  → Compression precision factor: 1
Added '9PM (Till I Come)' to playlist ''
AudioTrack copy constructor called for: Silence
[MP3Track::load] Loading MP3: "Silence" at 192 kbps...
[MP3Track::load] Loading MP3: "Silence" at 192 kbps...
  → Processing ID3 metadata (artist info, album art, etc.)...
  → Decoding MP3 frames...
  → Load complete.
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "Silence"
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "Silence"
  → Estimated beats: 840  → Compression precision factor: 0.6
Added 'Silence' to playlist ''
AudioTrack copy constructor called for: For An Angel
[WAVTrack::load] Loading WAV: "For An Angel" at 96000Hz/24bit (uncompressed)...
  → Estimated file size: 241920000 bytes
  → Fast loading due to uncompressed format.
[WAVTrack::analyze_beatgrid] Analyzing beat grid for: "For An Angel"
[WAVTrack::analyze_beatgrid] Analyzing beat grid for: "For An Angel"
  → Estimated beats: 945  → Precision factor: 1 (uncompressed audio)
Added 'For An Angel' to playlist ''

-- Processing: For An Angel --
[INFO] Found track: 'For An Angel' in playlist.
[System] Loading track 'For An Angel' to controller....
[LRUCache] HIT: Track 'For An Angel' served from slot 1.
[Controller] HIT: Track 'For An Angel' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: For An Angel

-- Processing: Silence --
[INFO] Found track: 'Silence' in playlist.
[System] Loading track 'Silence' to controller....
[LRUCache] HIT: Track 'Silence' served from slot 2.
[Controller] HIT: Track 'Silence' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: Silence

-- Processing: 9PM (Till I Come) --
[INFO] Found track: '9PM (Till I Come)' in playlist.
[System] Loading track '9PM (Till I Come)' to controller....
[LRUCache] HIT: Track '9PM (Till I Come)' served from slot 0.
[Controller] HIT: Track '9PM (Till I Come)' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: 9PM (Till I Come)

-- Processing: For An Angel --
[INFO] Found track: 'For An Angel' in playlist.
[System] Loading track 'For An Angel' to controller....
[LRUCache] HIT: Track 'For An Angel' served from slot 1.
[Controller] HIT: Track 'For An Angel' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: For An Angel

-- Processing: Silence --
[INFO] Found track: 'Silence' in playlist.
[System] Loading track 'Silence' to controller....
[LRUCache] HIT: Track 'Silence' served from slot 2.
[Controller] HIT: Track 'Silence' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: Silence

-- Processing: 9PM (Till I Come) --
[INFO] Found track: '9PM (Till I Come)' in playlist.
[System] Loading track '9PM (Till I Come)' to controller....
[LRUCache] HIT: Track '9PM (Till I Come)' served from slot 0.
[Controller] HIT: Track '9PM (Till I Come)' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: 9PM (Till I Come)

-- Processing: For An Angel --
[INFO] Found track: 'For An Angel' in playlist.
[System] Loading track 'For An Angel' to controller....
[LRUCache] HIT: Track 'For An Angel' served from slot 1.
[Controller] HIT: Track 'For An Angel' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: For An Angel

-- Processing: Silence --
[INFO] Found track: 'Silence' in playlist.
[System] Loading track 'Silence' to controller....
[LRUCache] HIT: Track 'Silence' served from slot 2.
[Controller] HIT: Track 'Silence' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: Silence

=== Loading Playlist: trance_classics ===
[System] Loading playlist: trance_classics
AudioTrack copy constructor called for: For An Angel
[WAVTrack::load] Loading WAV: "For An Angel" at 96000Hz/24bit (uncompressed)...
  → Estimated file size: 241920000 bytes
  → Fast loading due to uncompressed format.
[WAVTrack::analyze_beatgrid] Analyzing beat grid for: "For An Angel"
[WAVTrack::analyze_beatgrid] Analyzing beat grid for: "For An Angel"
  → Estimated beats: 945  → Precision factor: 1 (uncompressed audio)
Added 'For An Angel' to playlist ''
AudioTrack copy constructor called for: Silence
[MP3Track::load] Loading MP3: "Silence" at 192 kbps...
[MP3Track::load] Loading MP3: "Silence" at 192 kbps...
  → Processing ID3 metadata (artist info, album art, etc.)...
  → Decoding MP3 frames...
  → Load complete.
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "Silence"
[MP3Track::analyze_beatgrid] Analyzing beat grid for: "Silence"
  → Estimated beats: 840  → Compression precision factor: 0.6
Added 'Silence' to playlist ''

-- Processing: Silence --
[INFO] Found track: 'Silence' in playlist.
[System] Loading track 'Silence' to controller....
[LRUCache] HIT: Track 'Silence' served from slot 2.
[Controller] HIT: Track 'Silence' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: Silence

-- Processing: For An Angel --
[INFO] Found track: 'For An Angel' in playlist.
[System] Loading track 'For An Angel' to controller....
[LRUCache] HIT: Track 'For An Angel' served from slot 1.
[Controller] HIT: Track 'For An Angel' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: For An Angel

-- Processing: For An Angel --
[INFO] Found track: 'For An Angel' in playlist.
[System] Loading track 'For An Angel' to controller....
[LRUCache] HIT: Track 'For An Angel' served from slot 1.
[Controller] HIT: Track 'For An Angel' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: For An Angel

-- Processing: Silence --
[INFO] Found track: 'Silence' in playlist.
[System] Loading track 'Silence' to controller....
[LRUCache] HIT: Track 'Silence' served from slot 2.
[Controller] HIT: Track 'Silence' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: Silence

-- Processing: 9PM (Till I Come) --
[INFO] Found track: '9PM (Till I Come)' in playlist.
[System] Loading track '9PM (Till I Come)' to controller....
[LRUCache] HIT: Track '9PM (Till I Come)' served from slot 0.
[Controller] HIT: Track '9PM (Till I Come)' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: 9PM (Till I Come)

-- Processing: For An Angel --
[INFO] Found track: 'For An Angel' in playlist.
[System] Loading track 'For An Angel' to controller....
[LRUCache] HIT: Track 'For An Angel' served from slot 1.
[Controller] HIT: Track 'For An Angel' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: For An Angel

-- Processing: Silence --
[INFO] Found track: 'Silence' in playlist.
[System] Loading track 'Silence' to controller....
[LRUCache] HIT: Track 'Silence' served from slot 2.
[Controller] HIT: Track 'Silence' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: Silence

-- Processing: 9PM (Till I Come) --
[INFO] Found track: '9PM (Till I Come)' in playlist.
[System] Loading track '9PM (Till I Come)' to controller....
[LRUCache] HIT: Track '9PM (Till I Come)' served from slot 0.
[Controller] HIT: Track '9PM (Till I Come)' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: 9PM (Till I Come)

-- Processing: For An Angel --
[INFO] Found track: 'For An Angel' in playlist.
[System] Loading track 'For An Angel' to controller....
[LRUCache] HIT: Track 'For An Angel' served from slot 1.
[Controller] HIT: Track 'For An Angel' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: For An Angel

-- Processing: Silence --
[INFO] Found track: 'Silence' in playlist.
[System] Loading track 'Silence' to controller....
[LRUCache] HIT: Track 'Silence' served from slot 2.
[Controller] HIT: Track 'Silence' found in cache and access time refreshed.
[System] Delegating track transfer to MixingEngineService for: Silence

[System] All playlists processed.

=== DJ Session Summary ===
Session: Interactive Session
Tracks processed: 21
Cache hits: 18
Cache misses: 3
Cache evictions: 0
Deck A loads: 0
Deck B loads: 0
Transitions: 0
Errors: 21
=== Session Complete ===
============= INTERACTIVE SESSION ENDED =============

Shutting down DJ Session System: Interactive Session
[MixingEngineService] Destroying service and cleaning up decks.
[MixingEngineService] Destruction complete.
AudioTrack destructor called for: 9PM (Till I Come)
AudioTrack destructor called for: For An Angel
AudioTrack destructor called for: Silence
AudioTrack destructor called for: Silence
AudioTrack destructor called for: For An Angel
AudioTrack destructor called for: 9PM (Till I Come)
Destroying playlist: 
AudioTrack destructor called for: Silence
AudioTrack destructor called for: For An Angel
AudioTrack destructor called for: For An Angel
AudioTrack destructor called for: Silence
AudioTrack destructor called for: 9PM (Till I Come)
AudioTrack destructor called for: For An Angel
AudioTrack destructor called for: Silence
AudioTrack destructor called for: 9PM (Till I Come)
AudioTrack destructor called for: For An Angel
AudioTrack destructor called for: Silence
