#ifndef _MENUSTATE_HPP
#define _MENUSTATE_HPP

#include <list>
#include <vector>
#include <cstdlib>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "MenuWorld.hpp"
#include "Resources.hpp"
#include "GameState.hpp"
#include "GameStateManager.hpp"


class MenuState : public GameState {
  public:
    MenuState(GameStateManager& gsm, sf::Vector2u const& windowSize);
    ~MenuState();

    void init() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time) override;
    void resize(sf::Vector2u const windowSize) override;
    void keyPressed(sf::Event event) override;
    void mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates) override;

  private:
    mutable float zoom;
    size_t selectedItem;
    MenuWorld world;
    std::vector<std::string> menuEntryIds;
};

#endif
