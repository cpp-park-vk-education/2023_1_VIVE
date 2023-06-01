#pragma ocne

#include <SFML/Graphics.hpp>
#include <memory>

class CameraTarget {
public:

    CameraTarget(const sf::Vector2f& camera_size, const sf::FloatRect& restriction);

    CameraTarget() = delete;
    CameraTarget(const CameraTarget&) = delete;
    CameraTarget(CameraTarget&&) = delete;
    CameraTarget& operator=(const CameraTarget&) = delete;
    CameraTarget& operator=(CameraTarget&&) = delete;

    void setFollowByCoordinates(float x, float y);
    void setCameraSize(const sf::Vector2f& size);
    void setCameraViewport(const sf::FloatRect& viewport);
    void follow(const sf::Sprite& sprite);
    void unfollow();
    sf::Vector2f getCameraCenter() const;
    sf::Vector2f getCameraSize() const;
    sf::Vector2f getTopLeftCameraCoordinates() const;
    const sf::View& getView() const;

    ~CameraTarget() {
    }

private:
    void checkBound();

    sf::View camera_view_;
    sf::Vector2f camera_size_;
    sf::FloatRect restriction_;
};

using CameraTargetShPtr = std::shared_ptr<CameraTarget>;
