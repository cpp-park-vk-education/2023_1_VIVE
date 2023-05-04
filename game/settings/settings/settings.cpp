#include "settings.hpp"

bool Settings::saveDataParametrs() {

}

Settings::Settings() {

}

Settings::~Settings() {

}

bool Settings::setWindowSize(sf::Vector2u& window_size) {
    return true;
}

bool Settings::setMusicVolume(float parametr) {
    return true;
}

bool Settings::setSoundVolume(float parametr) {
    return true;
}

bool Settings::setDifficult(float parametr) {
    return true;
}

sf::Vector2u& Settings::getWindowSize() {
    sf::Vector2u invalid_vector;
    return invalid_vector;
}

float Settings::getMusicVolume() {
    return 0.0f;
}

float Settings::getSoundVolume() {
    return 0.0f;
}

float Settings::getDifficult() {
    return 0.0f;
}
