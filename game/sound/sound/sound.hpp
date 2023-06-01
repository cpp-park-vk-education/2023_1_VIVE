#pragma once

#include "i_sound.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include "queue"

class SoundManager : ISound {
public:
    static SoundManager* getInstance();
    ~SoundManager() override;

    void loadSoundAndMusicForLevel(const std::string& level_name);

    void playWinningMusic();

    void playMusic() override;
    void playSoundEffect(SoundType sound_type) override;

    void stopMusic() override;

    void setVolumeMusic(float volume = 100.0f) override;
    void setVolumeSoundEffect(float volume = 100.0f) override;

private:
    SoundManager();

    void clearHeap();

    void readConfigAndLoadMusic(const std::string& level_name);

    int8_t current_music_;

    float music_volume_;
    float sound_volume_;

    std::vector<sf::Music*> musics_;
    std::unordered_map<SoundType, sf::Sound> sounds_;
    std::unordered_map<SoundType, sf::SoundBuffer> sounds_buffer_;
};
