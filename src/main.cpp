#include <SFML/Graphics.hpp>
#include "../game/assetManager/asset_manager.hpp"
#include "../game/playerUserInterface/playerUserInterface/player_user_interface.hpp"

int main() {
    std::string level = "level_1";
    AssetManager::getInstance()->loadAssets(level);

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Atomic God");

    sf::Texture texture = AssetManager::getInstance()->getTexture("green_world_temple");

    sf::Vector2u windowSize = window.getSize();

    sf::Sprite sprite(texture);
    sprite.setScale(3.0f, 3.0f);

    PUI pui(windowSize);
    pui.updateBar(true, 59);
    pui.updateBar(false, 86);

    while(window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        pui.draw(window, sf::RenderStates());
        window.display();
    }
    
    return 0;
}
