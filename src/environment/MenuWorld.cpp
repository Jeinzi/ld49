#include "MenuWorld.hpp"


MenuWorld::MenuWorld(sf::Vector2u const& windowSize)
  : World(windowSize)
{
  calculateEarthCenter(windowSize);
}

bool MenuWorld::update(sf::Time time) {
  World::update(time);
  earthShape.setOrigin(0.9 * earthRadius, 0.9 * earthRadius);
  return true;
}


void MenuWorld::calculateEarthCenter(sf::Vector2u const windowSize) {
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
