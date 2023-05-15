#pragma once

#include "status_expirience.hpp"
#include "navigation_icons.hpp"
#include "status_weapon.hpp"
#include "status_money.hpp"
#include "status_bar.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Object : public sf::Drawable {
public:
    uint8_t getPriority() const {
        return priority_;
    }

    Object() {
    }

    virtual ~Object() {
    }

    virtual void initSprite() = 0;
    virtual void update(const sf::Event& event) = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
protected:
    uint8_t priority_;
    sf::Sprite sprite_;
};

class PUI : public Object {
public:
    PUI(const sf::Vector2u& camera_size);
    virtual ~PUI() override;

    PUI() = delete;
    PUI(const PUI&) = delete;
    PUI(PUI&&) = delete;
    PUI& operator=(const PUI&) = delete;
    PUI& operator=(PUI&&) = delete;

    virtual void initSprite() override;
    virtual void update(const sf::Event& event) override;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void changeResolution(const sf::Vector2u& camera_size);

    void updateWeapon(const std::string& name, const sf::Vector2u& camera_size);
    void updateBar(bool is_mana_bar, uint16_t status);
    void updateMaxStatusBar(bool is_mana_bar, uint16_t max_status);
    void updateMoney(uint16_t money);
    void updateExpirienceLevel(uint16_t total_level, uint16_t max_points);
    void updateExpirienceCurrentPoints(uint16_t current_points);

private:
    std::unique_ptr<StatusWeapon> weapon_status_;
    std::unique_ptr<StatusExpirience> status_expirience_;
    std::unique_ptr<StatusMoney> money_status_;
    std::unique_ptr<NavigationIcons> navigation_icons_;
    std::unique_ptr<StatusPlayerBar> health_bar_;
    std::unique_ptr<StatusPlayerBar> mana_bar_;
};
