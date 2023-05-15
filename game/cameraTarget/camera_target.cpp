#include "camera_target.hpp"
#include <iostream>

CameraTarget::CameraTarget(const sf::Vector2f& camera_size, const sf::FloatRect& restriction) 
                            : camera_size_(camera_size), restriction_(restriction) {
    setCameraSize(camera_size);
    setCameraViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
}

void CameraTarget::setFollowByCoordinates(float x, float y) {
    camera_view_.setCenter(x, y);
    checkBound();
}

void CameraTarget::setCameraSize(const sf::Vector2f& size) {
    camera_view_.setSize(camera_size_);
}

void CameraTarget::setCameraViewport(const sf::FloatRect& viewport) {
    camera_view_.setViewport(viewport);
}

void CameraTarget::follow(const sf::Sprite& sprite) {
    sf::FloatRect sprite_rect = sprite.getGlobalBounds();
    setFollowByCoordinates(sprite_rect.left + sprite_rect.width / 2.0f, sprite_rect.top + sprite_rect.height / 2.0f);
}

void CameraTarget::unfollow() {
    //Don't do nothing. Just stay at last position. It will on some scene (movie short) in future
}

sf::Vector2f CameraTarget::getCameraCenter() const {
    return camera_view_.getCenter();
}

sf::Vector2f CameraTarget::getCameraSize() const {
    return camera_size_;
}

sf::Vector2f CameraTarget::getTopLeftCameraCoordinates() const {
    sf::Vector2f center = camera_view_.getCenter();
    sf::Vector2f size = camera_size_;
    return center - 0.5f * size;
}

const sf::View& CameraTarget::getView() const {
    return camera_view_;
}

void CameraTarget::checkBound() {
    sf::Vector2f center = getCameraCenter();

    float half_width = camera_size_.x / 2.0f;
    float half_height = camera_size_.y / 2.0f;

    if (center.x - half_width < restriction_.left)
        center.x = restriction_.left + half_width;
    if (center.x + half_width > restriction_.left + restriction_.width)
        center.x = restriction_.left + restriction_.width - half_width;
    if (center.y - half_height < restriction_.top)
        center.y = restriction_.top + half_height;
    if (center.y + half_height > restriction_.top + restriction_.height)
        center.y = restriction_.top + restriction_.height - half_height;

    camera_view_.setCenter(center);
}
