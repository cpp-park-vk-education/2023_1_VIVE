#include "i_camera.hpp"

class Camera : public ICameraTarget {
public:
    Camera();
    ~Camera();
    void setCenter(sf::Vector2u& coordinates) override;
    void move(sf::Vector2u& offset) override;
    sf::Vector2u getCenter() override;
    sf::Vector2u getSize() override;
    sf::View getTarget() override;
    void update(float parametr) override;
    Camera& getInstance();
};
