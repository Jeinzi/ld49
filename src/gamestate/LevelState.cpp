#include "LevelState.hpp"
#include <SFML/System/Vector2.hpp>


LevelState::LevelState(GameStateManager& gsm, World& world)
  : GameState(gsm), zoom(1), world(world)
{
  for (int i = 0; i < 7; ++i) {
    sf::Vector2f pos(rand() % 1000, rand() % 700);
    sf::Vector2f v(-10*(rand() % 2 + 10), 0);
    clouds.emplace_back(pos, v);
  }
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
  //target.draw(world, states);
  target.clear(sf::Color(50, 110, 250, 255));
  for (auto const& c: clouds) {
    c.draw(target, states);
  }

  //jerrycan.draw(target, states);
  plane.draw(target, states);

  //target.setView(view);
}


void LevelState::update(sf::Time time) {
  //world.update(time);
  for (size_t i = 0; i < clouds.size(); ++i) {
    auto& c = clouds[i];
    c.update(time);
    if (!c.isVisible()) {
      c = Cloud({100,100}, {-20,0});
    }
  }
  jerrycan.update(time);
  plane.update(time);
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
