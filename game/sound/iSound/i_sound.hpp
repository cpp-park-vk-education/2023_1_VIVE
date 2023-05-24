#include <SFML/Audio.hpp>
#include "sound_type.hpp"
#include <string>

class ISound {
public:
    virtual ~ISound() = default;

    virtual void playMusic() = 0;
    virtual void playSoundEffect(SoundType sound_type) = 0;

    virtual void stopMusic() = 0;

    virtual void setVolumeMusic(float volume) = 0;
    virtual void setVolumeSoundEffect(float volume) = 0;
};