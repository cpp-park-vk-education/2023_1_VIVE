#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <unordered_map>
#include <filesystem>
#include <iostream>
#include <fstream>

enum FileType{
    TEXTURE,
    FONT,
};

class AssetManager {
public:
    static AssetManager* getInstance();

    AssetManager(const AssetManager&) = delete;
    AssetManager(AssetManager&&) = delete;
    AssetManager& operator=(const AssetManager&) = delete;
    AssetManager& operator=(AssetManager&&) = delete;

    bool loadAssets(const std::string& level);
    sf::Texture& getTexture(const std::string& name);
    sf::Font& getFont(const std::string& name);

private:
    AssetManager();
    ~AssetManager();
    void clearAssets();
    std::unordered_map<std::string, sf::Texture> textures_;
    std::unordered_map<std::string, sf::Font> fonts_;
};
