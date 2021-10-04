#ifndef _LEVELSTATE_HPP
#define _LEVELSTATE_HPP

#include <cstdlib>
#include <vector>

#include "Jerrycan.hpp"
#include "Resources.hpp"
#include "GameState.hpp"
#include "LevelWorld.hpp"
#include "GameStateManager.hpp"


class LevelState : public GameState {
  public:
    LevelState(GameStateManager& gsm);
    ~LevelState();

    void init() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time) override;
    void resize(sf::Vector2u const windowSize) override;
    void keyPressed(sf::Event event) override;
    void mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates) override;

  private:
    mutable float zoom;
    LevelWorld world;
    Jerrycan jerrycan;
};

#endif
