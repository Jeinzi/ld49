#include "LevelState.hpp"
#include "GameState.hpp"


LevelState::LevelState(GameStateManager& gsm, sf::Vector2u const& windowSize) :
  GameState(gsm),
  zoom(1),
  world(windowSize)
{}

LevelState::~LevelState() {}


void LevelState::init() {}

void LevelState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  world.draw(target, states);
}


void LevelState::update(sf::Time time) {
  if (!world.update(time)) {
    gsm.changeState(GameStateManager::State::Menu, true);
  }
}


void LevelState::resize(sf::Vector2u const windowSize) {
  world.resize(windowSize);
}


void LevelState::keyPressed(sf::Event e) {
  if (e.key.code == sf::Keyboard::Escape) {
    gsm.changeState(GameStateManager::State::Menu);
  }
  world.keyPressed(e);
}


void LevelState::mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates) {
  //player.mouseButtonPressed(event, worldCoordinates);
}
