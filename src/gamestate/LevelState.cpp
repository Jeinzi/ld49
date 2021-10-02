#include "LevelState.hpp"


LevelState::LevelState(GameStateManager& gsm, World& world)
  : GameState(gsm), zoom(1), world(world)
{

}

LevelState::~LevelState() {}


void LevelState::init() {
  //sf::Music& music = Resources::getMusic("dunes_at_night");
  //music.setLoop(true);
  //music.setVolume(5);
  //music.play();
}


void LevelState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  //auto view = target.getView();
  //view.zoom(zoom);
  //zoom = 1;
  //target.setView(view);

  // Draw world.
  target.draw(world, states);

  //target.setView(view);
}


void LevelState::update(sf::Time time) {
  //player.update(time);
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
