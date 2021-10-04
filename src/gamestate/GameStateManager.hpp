#ifndef _GAMESTATEMANAGER_HPP
#define _GAMESTATEMANAGER_HPP

#include <array>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

#include "GameState.hpp"

class GameState;


class GameStateManager : public sf::Drawable {
  public:
    enum class State {
      Menu,
      Level,
      TransitionIn
    };

    GameStateManager();
    ~GameStateManager();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool update(sf::Time time);
    void changeState(State state);
    void keyPressed(sf::Event event);
    void mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates);
    void mouseWheelMoved(sf::Event event);
    void resize(sf::Vector2u const windowSize);
    void exit();

  private:
    bool continueExecution;
    State currentState;
    std::vector<GameState*> states;
};

#endif

