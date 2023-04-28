#include "SFML/Graphics.hpp"

class StatusBar {
public:
    StatusBar(const std::string& image, const std::string& font, unsigned int window_size_x, unsigned int window_size_y, bool is_mana);

    void setStatus(int status);

    void draw(sf::RenderWindow& window) const;

    StatusBar(const StatusBar&) = delete;
    StatusBar(const StatusBar&&) = delete;

    StatusBar& operator=(const StatusBar&) = delete;
    StatusBar& operator=(const StatusBar&&) = delete;

private:
    sf::Texture icon_texture_;
    sf::Sprite icon_sprite_;
    sf::RectangleShape bar_background_;
    sf::RectangleShape bar_;
    sf::Font font_;
    sf::Text procent_;
    int max_status_;
    int current_status_;
};
