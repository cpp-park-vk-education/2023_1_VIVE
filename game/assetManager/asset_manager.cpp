#include "asset_manager.hpp"
#include <filesystem>
#include <iostream>
#include <fstream>

AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {

}

AssetManager* AssetManager::getInstance() {
    static AssetManager am;
    return &am;
}

void AssetManager::clearAssets() {
    textures_.clear();
    fonts_.clear();
    sounds_buffer_.clear();
}

bool AssetManager::loadAssets(const std::string& level) {
    clearAssets();

    std::filesystem::path path_to_data_folder = std::filesystem::current_path().parent_path() / "game" / "assetManager" / "data";
    
    for (const auto& entry : std::filesystem::directory_iterator(path_to_data_folder)) {
        if (entry.path().stem().string() == level) {
            path_to_data_folder = entry.path();
            break;
        }
    }

    std::fstream file(path_to_data_folder);
    path_to_data_folder = path_to_data_folder.parent_path() / "assets";

    if (!file.is_open()) {
        std::cerr << "File is not existing. Make sure that you install the correct version of our game!" << std::endl;
        return false;
    }

    std::string name, type, path;
    while(file >> name >> type >> path) {
        std::filesystem::path path_to_file = path_to_data_folder / path;
        if (type == "texture") {

            sf::Texture texture; 
            if (!texture.loadFromFile(path_to_file)) {
                std::cerr << "File is not existing. Make sure that you install the correct version of our game!" << std::endl;
                return false;
            }
            textures_[name] = texture;

        } else if (type == "sound") {

            sf::SoundBuffer sb;
            if (!sb.loadFromFile(path_to_file)) {
                std::cerr << "File is not existing. Make sure that you install the correct version of our game!" << std::endl;
                return false;
            }
            sounds_buffer_[name] = sb;

        } else if (type == "font") {

            sf::Font font;
            if (!font.loadFromFile(path_to_file)) {
                std::cerr << "File is not existing. Make sure that you install the correct version of our game!" << std::endl;
                return false;
            }
            fonts_[name] = font;

        }
    }

    return true;
}

sf::Texture& AssetManager::getTexture(const std::string& name) {
    return textures_[name];
}

sf::Font& AssetManager::getFont(const std::string& name) {
    return fonts_[name];
}

sf::SoundBuffer& AssetManager::getSoundBuffer(const std::string& name) {
    return sounds_buffer_[name];
}
