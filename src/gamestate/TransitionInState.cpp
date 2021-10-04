#include "TransitionInState.hpp"
#include "GameState.hpp"
#include "Resources.hpp"


TransitionInState::TransitionInState(GameStateManager& gsm, World& world)
  : GameState(gsm), cumulatedTransitionTime(0), zoom(1), transitionDuration(5), world(world)
{

}

TransitionInState::~TransitionInState() {}


void TransitionInState::init() {
  cumulatedTransitionTime = 0;
}


void TransitionInState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(world, states);

  auto oldView = target.getView();
  auto windowSize = target.getSize();
  sf::Vector2f viewSize(windowSize.x, windowSize.y);
  sf::Vector2f center(windowSize.x / 2.f, windowSize.y / 2.f);
  sf::View view(center, viewSize);
  target.setView(view);

  // Get screen size.
  auto w = target.getSize().x;
  auto h = target.getSize().y;
}


void TransitionInState::update(sf::Time time) {
  cumulatedTransitionTime += time.asSeconds();
  world.update(time);

  // Transistion origin.


  // Transistion angular velocity.

  // Transistion to game state.
  if (true || cumulatedTransitionTime >= transitionDuration) {
    gsm.changeState(GameStateManager::State::Level);
  }
}


void TransitionInState::keyPressed(sf::Event event) {

}


void TransitionInState::mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates) {
  //player.mouseButtonPressed(event, worldCoordinates);
}
