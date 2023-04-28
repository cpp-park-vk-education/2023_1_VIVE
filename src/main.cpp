#include "SFML/Graphics.hpp"
#include "pui.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Atomic God");

    sf::Texture texture;
    if (!texture.loadFromFile("../assets/backgrounds/level1.1.png")) {
        return 1;
    }

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = texture.getSize();

    sf::Sprite sprite(texture);
    sprite.setScale(static_cast<float>(windowSize.x) / textureSize.x, static_cast<float>(windowSize.y) / textureSize.y);

    PUI pui(window);
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
        pui.drawPUI(window);
        window.display();
    }

    return 0;
}
