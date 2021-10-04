#include "Jerrycan.hpp"


Jerrycan::Jerrycan()
  : position(400, 500),
    animationDefault("jerrycan", {1}),
    currentAnimation(animationDefault)
{
  animationDefault.setHeight(50);
}

void Jerrycan::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  currentAnimation.get().draw(target, states);
}


void Jerrycan::update(sf::Time time) {
  currentAnimation.get().update(time);
  currentAnimation.get().setPosition(position);
}
