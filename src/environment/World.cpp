#include "World.hpp"
#include "Resources.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <ostream>


World::World()
  : dayLengthMins(1), timeMins(0.45 * dayLengthMins), skyColor(50, 110, 250, 255),
    starField(100)
{

}


void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.clear(sf::Color::Black);
  starField.draw(target, states);
  
  // Draw earth.
  sf::CircleShape e;
  e.setRadius(earthRadius);
  e.setPosition(earthPosition);
  e.setPointCount(200);
  e.setTexture(&Resources::getTexture("earth-1"));
  e.setOrigin(0.9 * earthRadius, 0.9 * earthRadius);
  e.setRotation(timeMins / dayLengthMins * 360);
  target.draw(e, states);
}


void World::update(sf::Time time) {
  timeMins += time.asSeconds() / 60;
}


void World::resize(sf::Vector2u const windowSize) {
  calculateEarthCenter(windowSize);
}


void World::calculateEarthCenter(sf::Vector2u const windowSize) {
  float heightSide = 0.46 * windowSize.x;
  float heightCenter = 0.5 * windowSize.x;
  
  // Define two points and a vector connecting them.
  sf::Vector2f c(heightCenter, windowSize.y / 2.f);
  sf::Vector2f s(heightSide, windowSize.y);
  auto cs = s - c;

  // Calculate normals.
  sf::Vector2f ns(-cs.y, cs.x);
  sf::Vector2f nc(-1, 0);

  // The intersection is the point on the other side of the planet
  // in relation to c.
  auto r = calculateIntersection(c, s, nc, ns);
  earthRadius = -(r.x - heightCenter) / 2;
  earthPosition.x = heightCenter - earthRadius;
  earthPosition.y = windowSize.y / 2.f;
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
