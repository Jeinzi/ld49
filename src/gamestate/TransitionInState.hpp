#ifndef _TRANSITIONINSTATE_HPP
#define _TRANSITIONINSTATE_HPP

#include <list>
#include <vector>
#include <cstdlib>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "MenuWorld.hpp"
#include "Resources.hpp"
#include "GameState.hpp"
#include "GameStateManager.hpp"


class TransitionInState : public GameState {
  public:
    TransitionInState(GameStateManager& gsm, sf::Vector2u const& windowSize);
    ~TransitionInState();

    void init() override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time) override;
    void resize(sf::Vector2u const windowSize) override;
    void keyPressed(sf::Event event) override;
    void mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates) override;

  private:
    float cumulatedTransitionTime;
    mutable float zoom;
    unsigned int transitionDuration;
    MenuWorld world;
};

#endif
