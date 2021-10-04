#include "LevelState.hpp"


LevelState::LevelState(GameStateManager& gsm)
  : GameState(gsm), zoom(1)
{
  
}

LevelState::~LevelState() {}


void LevelState::init() {}

void LevelState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  world.draw(target, states);
}


void LevelState::update(sf::Time time) {
  world.update(time);
  jerrycan.update(time);
}


void LevelState::resize(sf::Vector2u const windowSize) {
  world.resize(windowSize);
}


void LevelState::keyPressed(sf::Event event) {
  // Confirm entry.
  if (event.key.code == sf::Keyboard::Escape) {
    gsm.changeState(GameStateManager::State::Menu);
  }
}


void LevelState::mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates) {
  //player.mouseButtonPressed(event, worldCoordinates);
}
