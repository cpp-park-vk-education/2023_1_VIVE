#include "i_settings.hpp"

class Settings : public ISettings {
public:
    bool setWindowSize(sf::Vector2u& window_size) override;
    bool setMusicVolume(float parametr) override;
    bool setSoundVolume(float parametr) override;
    bool setDifficult(float parametr) override;
    sf::Vector2u& getWindowSize() override;
    float getMusicVolume() override;
    float getSoundVolume() override;
    float getDifficult() override;
    bool saveDataParametrs();
    virtual ~Settings() override;
    Settings();
};
