#include "SFML/Graphics.hpp"

class ISettings {
public:
    virtual bool setWindowSize(sf::Vector2u& window_size) = 0;
    virtual bool setMusicVolume(float parametr) = 0;
    virtual bool setSoundVolume(float parametr) = 0;
    virtual bool setDifficult(float parametr) = 0;
    virtual sf::Vector2u& getWindowSize() = 0;
    virtual float getMusicVolume() = 0;
    virtual float getSoundVolume() = 0;
    virtual float getDifficult() = 0; 
    virtual ~ISettings();
    ISettings();

private:
    sf::Vector2u window_size_;
    float music_volume_;
    float sound_volume_;
    float difficult_;
    int max_parametr_;
};
