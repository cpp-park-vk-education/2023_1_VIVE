#pragma once

#include "SFML/Graphics.hpp"

#include "Button.hpp"

#include <vector>
#include <memory>

class Menu {
    using ButtonShPtr = std::shared_ptr<Button>;
 private:

 public:
    explicit Menu(sf::RenderWindow* w);
    void open();

    void update(const sf::Event& event);
    void render();

    bool isOpen() const;
    bool isStart() const;
    bool isLoadGame() const;
    bool isAbout() const;

 private:
    sf::RenderWindow* window;

    bool isStartField = false;
    bool isAboutField = false;
    bool isLoadGameField = false;

    std::vector<ButtonShPtr> buttons;
    std::vector<std::pair<std::string, bool>> btnIsPressed{
            {"Start",     isStartField},
            {"Load game", isLoadGameField},
            {"About",     isAboutField},
    };

    bool isOpenField = false;
};


