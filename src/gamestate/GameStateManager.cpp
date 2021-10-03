#include "GameStateManager.hpp"

// These includes need to happen here in the cpp file, because if
// they are added to the hpp file, a circular dependency happens.
// In short, when a state inherits from GameState during its
// definition, GameState is not yet defined and a forward
// declaration does not work.
#include "MenuState.hpp"
#include "LevelState.hpp"


GameStateManager::GameStateManager()
  : continueExecution(true), world() {
  states.reserve(2);
  states.push_back(new MenuState(*this, world));
  states.push_back(new LevelState(*this, world));

  changeState(State::Menu);
}


GameStateManager::~GameStateManager() {

}

void GameStateManager::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(*this->states[(int)currentState], states);
}


bool GameStateManager::update(sf::Time time) {
  states[(int)currentState]->update(time);
  return continueExecution;
}


void GameStateManager::changeState(State state) {
  currentState = state;
  states[(int)currentState]->init();
}


void GameStateManager::keyPressed(sf::Event event) {
  states[(int)currentState]->keyPressed(event);
}


void GameStateManager::mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates) {
  states[(int)currentState]->mouseButtonPressed(event, worldCoordinates);
}


void GameStateManager::mouseWheelMoved(sf::Event event) {
  states[(int)currentState]->mouseWheelMoved(event);
}

void GameStateManager::exit() {
  continueExecution = false;
}

void GameStateManager::resize(sf::Vector2u const screenSize) {
  world.resize(screenSize);
}
