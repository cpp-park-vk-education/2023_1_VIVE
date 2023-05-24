#pragma once

#include "i_sound.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>
#include "queue"

class SoundManager : ISound {
public:
    static SoundManager* getInstance();

    void loadSoundAndMusicForLevel(const std::string& level_name);

    void playMusic() override;
    void playSoundEffect(SoundType sound_type) override;

    void stopMusic() override;

    void setVolumeMusic(float volume = 100.0f) override;
    void setVolumeSoundEffect(float volume = 100.0f) override;

    bool isSoundEffectPlay(const std::string& name) override;
    bool isMusicPlay(const std::string& name) override;

    bool isSoundEffectStop(const std::string& name) override;
    bool isMusicStop(const std::string& name) override;

private:
    SoundManager();
    ~SoundManager() override;

    void clearHeap();

    void readConfigAndLoadMusic(const std::string& level_name);
    void loadSoundEffects(const std::string& level_name);


    int8_t current_music_;
    std::vector<sf::Music*> musics_;
    std::unordered_map<SoundType, sf::Sound> sounds_;
};
