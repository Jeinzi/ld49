#include "GameStateManager.hpp"

// These includes need to happen here in the cpp file, because if
// they are added to the hpp file, a circular dependency happens.
// In short, when a state inherits from GameState during its
// definition, GameState is not yet defined and a forward
// declaration does not work.
#include "MenuState.hpp"
#include "LevelState.hpp"
#include "TransitionInState.hpp"


GameStateManager::GameStateManager(sf::Vector2u const& windowSize) :
  continueExecution(true),
  windowSize(windowSize)
{
  states.reserve(2);
  states.push_back(new MenuState(*this, windowSize));
  states.push_back(new LevelState(*this, windowSize));
  states.push_back(new TransitionInState(*this, windowSize));

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


void GameStateManager::changeState(State state, bool renewCurrentState) {
  if (renewCurrentState) {
    delete states[(int)currentState];
    states[(int)currentState] = new LevelState(*this, windowSize); // TODO this doesn't work generally
  }
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

void GameStateManager::resize(sf::Vector2u const windowSize) {
  this->windowSize = windowSize;
  for (auto& s: states) {
    s->resize(windowSize);
  }
}
