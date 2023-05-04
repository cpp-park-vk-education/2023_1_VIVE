#include "camera.hpp"

Camera::Camera() {

}

Camera::~Camera() {

}

Camera& Camera::getInstance() {
    static Camera camera;
    return camera;
}

void Camera::setCenter(sf::Vector2u& coordinates) {

}

void Camera::move(sf::Vector2u& offset) {
    
}

sf::Vector2u Camera::getCenter() {
    sf::Vector2u invalidVector;
    return invalidVector;
}

sf::Vector2u Camera::getSize() {
    sf::Vector2u invalidVector;
    return invalidVector;
}

sf::View Camera::getTarget() {
    sf::View invalidView;
    return invalidView;
}

void Camera::update(float parametr) {

}
