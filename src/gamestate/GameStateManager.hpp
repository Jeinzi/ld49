#ifndef _GAMESTATEMANAGER_HPP
#define _GAMESTATEMANAGER_HPP

#include <SFML/System/Vector2.hpp>
#include <array>
#include "SFML/Graphics.hpp"

#include "GameState.hpp"
#include "World.hpp"

class GameState;


class GameStateManager : public sf::Drawable {
  public:
    enum class State {
      Menu,
      Level
    };

    GameStateManager();
    ~GameStateManager();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool update(sf::Time time);
    void changeState(State state);
    void keyPressed(sf::Event event);
    void mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates);
    void mouseWheelMoved(sf::Event event);
    void resize(sf::Vector2u const screenSize);
    void exit();

  private:
    bool continueExecution;
    State currentState;
    World world;
    std::vector<GameState*> states;
};

#endif

