#include <SFML/Graphics.hpp>
#include "asset_manager.hpp"
#include "camera_target.hpp"
#include "player_user_interface.hpp"
#include <iostream>
#include <filesystem>

int main() {
    std::string level = "level_1";
    AssetManager::getInstance()->loadAssets(level);

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Atomic God");

    sf::Texture texture = AssetManager::getInstance()->getTexture("green_world_temple");

    sf::Vector2u windowSize = window.getSize();

    sf::Sprite sprite(texture);
    sprite.setScale(3.0f, 3.0f);

    sf::Vector2f camera_size = sf::Vector2f(windowSize.x, windowSize.y);
    sf::FloatRect camera_restriction = sprite.getGlobalBounds();

    CameraTarget camera(camera_size, camera_restriction);
    camera.setFollowByCoordinates(0, 0);

    PUI pui(camera_size, camera.getTopLeftCameraCoordinates());
    pui.updateBar(true, 59);
    pui.updateBar(false, 86);
    pui.updateMaxStatusBar(true, 500);
    pui.updateMaxStatusBar(false, 500);
    pui.updateBar(true, 471);
    pui.updateBar(false, 399);

    pui.updateExpirienceLevel(10, 200);
    pui.updateExpirienceCurrentPoints(14);

    camera.setFollowByCoordinates(2500, 1000);
    pui.updateCoordinates(camera.getCameraSize(), camera.getTopLeftCameraCoordinates());

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.setView(camera.getView());
        window.draw(sprite);
        pui.draw(window, sf::RenderStates());
        window.display();
    }
    
    return 0;
}
