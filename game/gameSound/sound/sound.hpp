#include "i_sound.hpp"
#include "SFML/Audio.hpp"

class Sound : public ISound {
public:
    Sound();
    ~Sound();
    void play() override;
    void stop() override;
    void setLoop(bool condition) override;
    bool getLoop() override;
    void setVolume(float parametr) override;
    bool isPlaying() override;
    bool isStoped() override;
    void setSound(std::string& sound_name);
    void setBackSound(std::string& bg_sound_name);
    void playBackSound();
    bool isBgSoundPlaying();
private:
    sf::Sound sound_;
    sf::Sound back_sound_;
};
