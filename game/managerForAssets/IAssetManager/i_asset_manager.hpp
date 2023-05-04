#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <map>
#include <string>

class IAssetManager {
public:
    virtual bool loadTexture(std::string& texture_name, std::string& path_to_texture) = 0;
    virtual sf::Texture getTexture(std::string& texture_name) = 0;
    virtual bool loadFont(std::string& font_name, std::string& path_to_font) = 0;
    virtual sf::Font getFont(std::string& font_name) = 0;
    virtual bool loadSound(std::string& sound_name, std::string& path_to_sound) = 0;
    virtual sf::SoundBuffer getSound(std::string& sound_name) = 0;
    virtual bool clearData() = 0;
    virtual bool loadAllFilesFromData(std::string&) = 0;
    virtual ~IAssetManager();
    IAssetManager();
private:
    std::map<std::string, sf::Texture> textures_;
    std::map<std::string, sf::Font> fonts_;
    std::map<std::string, sf::SoundBuffer> sounds_;
};
