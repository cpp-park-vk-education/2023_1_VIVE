#pragma ocne

#include <SFML/Graphics.hpp>

class CameraTarget {
public:

    CameraTarget(const sf::Vector2u& camera_size, const sf::FloatRect& restriction);

    CameraTarget() = delete;
    CameraTarget(const CameraTarget&) = delete;
    CameraTarget(CameraTarget&&) = delete;
    CameraTarget& operator=(const CameraTarget&) = delete;
    CameraTarget& operator=(CameraTarget&&) = delete;

    void setCenter(uint x, uint y);
    void setCameraSize(const sf::Vector2u& size);
    void follow(sf::Sprite sprite);
    void unfollow();
    sf::Vector2f getCenter() const;

    ~CameraTarget() {
    }

private:
    void checkBound();

    sf::View camera_view_;
    sf::Vector2u camera_size_;
    sf::FloatRect restriction_;
};
