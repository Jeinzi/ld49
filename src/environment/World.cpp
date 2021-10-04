#include "World.hpp"
#include "Resources.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <ostream>


sf::Vector2u World::windowSize;

World::World()
  : dayLengthMins(1), timeMins(0.45 * dayLengthMins), skyColor(sf::Color::Black),
    starField(100)
{
  earthShape.setTexture(&Resources::getTexture("earth-1"));
  earthShape.setPointCount(100);
}


void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.clear(skyColor);
  starField.draw(target, states);
  target.draw(earthShape, states);
}


bool World::update(sf::Time time) {
  timeMins += time.asSeconds() / 60;
  earthShape.setRadius(earthRadius);
  earthShape.setPosition(earthPosition);
  earthShape.setRotation(-timeMins / dayLengthMins * 360);
  return true;
}


void World::resize(sf::Vector2u const windowSize) {
  this->windowSize = windowSize;
  calculateEarthCenter(windowSize);
}


sf::Vector2f World::calculateIntersection(sf::Vector2f const p1,
                                          sf::Vector2f const p2,
                                          sf::Vector2f const v1,
                                          sf::Vector2f const v2) const
{
  auto f1 = p1.y - p2.y - v2.y/v2.x * (p1.x - p2.x);
  f1 /= (v1.x / v2.x * v2.y - v1.y);

  return p1 + f1 * v1;
}
