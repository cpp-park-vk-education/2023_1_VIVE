#include "SFML/Graphics.hpp"
#include "status_bar.hpp"

const std::string assets[] = {
    "../assets/fonts/EightBits.ttf",
    "../assets/objects/Heart.png",
    "../assets/objects/Mana.png",
    "../assets/objects/Sword.png",
    "../assets/objects/Level.png",
    "../assets/objects/Coin.png",
};

class PUI {
public:
    PUI(sf::RenderWindow& window);

    void updateBar(bool is_mana_bar, int status);

    void drawPUI(sf::RenderWindow& window) const;

    PUI(const PUI&) = delete;
    PUI(const PUI&&) = delete;

    PUI& operator=(const PUI&) = delete;
    PUI& operator=(const PUI&&) = delete;

    ~PUI();

private:
    StatusBar* health_bar_;
    StatusBar* mana_bar_;
};
