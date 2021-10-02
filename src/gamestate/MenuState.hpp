#ifndef _MENUSTATE_HPP
#define _MENUSTATE_HPP

#include <SFML/Graphics/Text.hpp>
#include <list>
#include <vector>
#include <cstdlib>

#include "World.hpp"
#include "Resources.hpp"
#include "GameState.hpp"
#include "GameStateManager.hpp"


class MenuState : public GameState {
  public:
    MenuState(GameStateManager& gsm, World& world);
    ~MenuState();

    void init() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time) override;
    void keyPressed(sf::Event event) override;
    void mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates) override;

  private:
    mutable float zoom;
    size_t selectedItem;
    World& world;
    std::vector<std::string> menuEntryIds;
};

#endif
