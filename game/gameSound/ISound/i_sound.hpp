class ISound {
public:
    virtual void play() = 0;
    virtual void stop() = 0;
    virtual void setLoop(bool condition) = 0;
    virtual bool getLoop() = 0;
    virtual void setVolume(float parametr) = 0;
    virtual bool isPlaying() = 0;
    virtual bool isStoped() = 0;
    virtual ~ISound();
    ISound();
};
