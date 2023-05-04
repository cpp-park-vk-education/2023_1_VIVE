#include "asset_manager.hpp"

bool AssetManager::loadTexture(std::string& texture_name, std::string& path_to_texture) {
    return true;
}

sf::Texture getTexture(std::string& texture_name) {
    sf::Texture invalidTexture;
    invalidTexture.create(0,0);
    return invalidTexture;
}

bool AssetManager::loadFont(std::string& font_name, std::string& path_to_font) {
    return true;
}

sf::Font AssetManager::getFont(std::string& font_name) {
    sf::Font invalidFont;
    return invalidFont;
}

bool AssetManager::loadSound(std::string& sound_name, std::string& path_to_sound) {
    return true;
}

sf::SoundBuffer AssetManager::getSound(std::string& sound_name) {
    sf::SoundBuffer invalidBuffer;
    return invalidBuffer;
}

bool AssetManager::clearData() {
    return true;
}

bool AssetManager::loadAllFilesFromData(std::string&) {
    return true;
}
