#include "Menu.hpp"
#include "Button.hpp"

Menu::Menu(sf::RenderWindow* w) {
    window = w;
}

void Menu::open() {
    isOpenField = true;
    {
        int i = 0;
        for (const auto& btn : btnIsPressed) {
            ButtonShPtr newBtn = std::make_shared<Button>(btn.first, 35, "fonts/EightBits.ttf", 0, 10, sf::Color::Red);
            newBtn->setPosition(100, float(i + 1) * 100);
            buttons.push_back(newBtn);
            i++;
        }
    }
}

void Menu::update(const sf::Event& event) {
    if (event.type == sf::Event::MouseMoved) {
        for (const auto& btn : buttons) {
            if (btn->isMouseOver(*window)) {
                btn->setBackColor(sf::Color(210, 210, 210));
            } else {
                btn->resetBackColor();
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        for (const auto& btn : buttons) {
            if (btn->isMouseOver(*window)) {
                isOpenField = false;
            }
        }
    }
}

void Menu::render() {
    for (int i = 0; i < buttons.size(); ++i) {
        window->draw(*buttons[i]);
    }
}

bool Menu::isOpen() const{
    return isOpenField;
}

bool Menu::isStart() const{
    return isStartField;
}

bool Menu::isLoadGame() const {
    return isLoadGameField;
}

bool Menu::isAbout() const {
    return isAboutField;
}
