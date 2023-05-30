#include "asset_manager.hpp"

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
}

bool AssetManager::loadAssets(const std::string& level) {
    clearAssets();

    std::cout << level << std::endl;

    std::filesystem::path path_to_config_folder = std::filesystem::current_path().parent_path() / "game" / "assetManager" / "config";
    
    for (const auto& entry : std::filesystem::directory_iterator(path_to_config_folder)) {
        if (entry.path().stem().string() == level) {
            path_to_config_folder = entry.path();
            break;
        }
    }

    std::fstream file(path_to_config_folder);
    path_to_config_folder = std::filesystem::current_path().parent_path() / "assets";

    if (!file.is_open()) {
        std::cerr << "AssetManager: AssetsFolder is not existing. Make sure that you install the correct version of our game!" << std::endl;
        return false;
    }

    int type;
    std::string name, path;
    while(file >> name >> type >> path) {
        std::filesystem::path path_to_file = path_to_config_folder / path;

        if (type == FileType::TEXTURE) {
            sf::Texture texture; 
            if (!texture.loadFromFile(path_to_file)) {
                std::cerr << "File is not existing. Make sure that you install the correct version of our game!" << std::endl;
                return false;
            }
            textures_[name] = texture;

        } else if (type == FileType::FONT) {
            sf::Font font;
            if (!font.loadFromFile(path_to_file)) {
                std::cerr << "File is not existing. Make sure that you install the correct version of our game!" << std::endl;
                return false;
            }
            fonts_[name] = font;

        }
    }

    file.close();

    return true;
}

sf::Texture& AssetManager::getTexture(const std::string& name) {
    return textures_[name];
}

sf::Font& AssetManager::getFont(const std::string& name) {
    return fonts_[name];
}
