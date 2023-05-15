#include "camera_target.hpp"

CameraTarget::CameraTarget(const sf::Vector2u& camera_size, const sf::FloatRect& restriction) {
    camera_size_ = camera_size;
    restriction_ = restriction;

    setCameraSize(camera_size_);
}

void CameraTarget::setCenter(uint x, uint y) {

}

void CameraTarget::setCameraSize(const sf::Vector2u& size) {
}

void CameraTarget::follow(sf::Sprite sprite) {

}

void CameraTarget::unfollow() {

}

sf::Vector2f CameraTarget::getCenter() const {
    return camera_view_.getCenter();
}

void CameraTarget::checkBound() {
    sf::Vector2f center = getCenter();

    float half_view_width = camera_size_.x / 2.0f;
    float half_view_height = camera_size_.y / 2.0f;
    float left_rest = center.x - half_view_width;
    float right_rest = center.x + half_view_width;
    float up_rest = center.y - half_view_height;
    float down_rest = center.y + half_view_height;

    if (left_rest < restriction_.left)
        center.x = restriction_.left + half_view_width;
    if (right_rest > restriction_.left + restriction_.width)
        center.x = restriction_.left + restriction_.width - half_view_width;
    if (up_rest < restriction_.top)
        center.y = restriction_.top + half_view_height;
    if (down_rest > restriction_.top + restriction_.height)
        center.y = restriction_.top + restriction_.height - half_view_height;

    if (center != getCenter())
        camera_view_.setCenter(center);
}
