#include "i_asset_manager.hpp"

class AssetManager : public IAssetManager {
public:
    bool loadTexture(std::string& texture_name, std::string& path_to_texture) override;
    sf::Texture getTexture(std::string& texture_name) override;
    bool loadFont(std::string& font_name, std::string& path_to_font) override;
    sf::Font getFont(std::string& font_name) override;
    bool loadSound(std::string& sound_name, std::string& path_to_sound) override;
    sf::SoundBuffer getSound(std::string& sound_name) override;
    bool clearData() override;
    bool loadAllFilesFromData(std::string&) override;
    AssetManager() {}
    virtual ~AssetManager() override {}
};
