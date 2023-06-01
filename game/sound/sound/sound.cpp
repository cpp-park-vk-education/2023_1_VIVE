#include "sound.hpp"

SoundManager::SoundManager() : current_music_(-1), music_volume_(100.0f), sound_volume_(100.0f) {
}

SoundManager::~SoundManager() {
    clearHeap();
}

SoundManager *SoundManager::getInstance() {
    static SoundManager sm;
    return &sm;
}

void SoundManager::loadSoundAndMusicForLevel(const std::string &level_name) {
    clearHeap();
    readConfigAndLoadMusic(level_name);
}

void SoundManager::playWinningMusic() {
    musics_[current_music_]->stop();
    current_music_ = 1;
    musics_[current_music_]->play();
}

void SoundManager::playMusic() {
    if (current_music_ == -1) {
        ++current_music_;
        musics_[current_music_]->play();
        return;
    }

    if (musics_[current_music_]->getStatus() == sf::SoundSource::Stopped) {
        musics_[current_music_]->stop();
        ++current_music_;

        if (current_music_ == musics_.size()) {
            current_music_ = -1;
            return;
        }

        musics_[current_music_]->setVolume(music_volume_);
        musics_[current_music_]->play();
    }
}

void SoundManager::playSoundEffect(SoundType sound_type) {
    if (sounds_[sound_type].getStatus() == sf::SoundSource::Playing) {
        if (sound_type > SoundType::MUSIC && sound_type < SoundType::ENEMY_CLOSE_ATTACK)
            sounds_[sound_type].stop();
        else if (sound_type == SoundType::RUNNING)
            return;
        else if (sound_type == SoundType::ENEMY_DEATH || sound_type == SoundType::PLAYER_DEATH)
            return;
    }

    sounds_[sound_type].setVolume(sound_volume_);
    sounds_[sound_type].play();
}

void SoundManager::stopMusic() {
    if (current_music_ == -1)
        return;

    musics_[current_music_]->stop();
}

void SoundManager::setVolumeMusic(float volume) {
    music_volume_ = volume;
}

void SoundManager::setVolumeSoundEffect(float volume) {
    sound_volume_ = volume;
}

void SoundManager::clearHeap() {
    stopMusic();

    while(!musics_.empty()) {
        sf::Music* ms = musics_.back();
        musics_.pop_back();

        delete ms;
    }

    sounds_.clear();
    sounds_buffer_.clear();

    current_music_ = -1;
}

void SoundManager::readConfigAndLoadMusic(const std::string& file_name) {
    std::filesystem::path path_to_assets = std::filesystem::current_path().parent_path() / "assets";
    std::filesystem::path path_to_config_file = std::filesystem::current_path().parent_path() / "game" / "sound" / "sound" / "config" / std::string(file_name + ".txt");
    if (!path_to_config_file.has_filename()) {
        std::cerr << "File is not existing. Make sure that you install the correct version of our game!" << std::endl;
        return;
    }

    std::string ppp = path_to_config_file;

    std::fstream config_file(path_to_config_file);

    if (config_file.fail()) {
        std::cerr << "File is not existing. Make sure that you install the correct version of our game!" << std::endl;
        return;
    }

    std::string path;
    int type;

    while (config_file >> path >> type) {
        std::filesystem::path path_to_music_file = path_to_assets / path;

        if (!path_to_music_file.has_filename()) {
            std::cerr << "Music" << path_to_music_file.filename() << "is not existing. Make sure that you install the correct version of our game!" << std::endl;
            return;
        }

        if (type == SoundType::MUSIC) {
            sf::Music* music = new sf::Music;
            music->openFromFile(path_to_music_file);
            musics_.push_back(music);
        } else {
            SoundType type_sound = static_cast<SoundType>(type);

            std::cout << type << std::endl;
            std::cout << static_cast<SoundType>(type) << std::endl;

            if (!sounds_buffer_[type_sound].loadFromFile(path_to_music_file)) {
                std::cerr << "Sound" << path_to_music_file.filename() << "is not existing. Make sure that you install the correct version of our game!" << std::endl;
                return;
            }

            sounds_[type_sound].setBuffer(sounds_buffer_[type_sound]);
        }
    }

    config_file.close();
}
