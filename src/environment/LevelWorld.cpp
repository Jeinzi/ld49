#include "LevelWorld.hpp"


LevelWorld::LevelWorld() {
  skyColor = sf::Color(50, 110, 250, 255);
}


void LevelWorld::calculateEarthCenter(sf::Vector2u const windowSize) {
  float heightSide = 0.15 * windowSize.y;
  float heightCenter = 0.2 * windowSize.y;
  
  // Define two points and a vector connecting them.
  sf::Vector2f c(windowSize.x / 2.f, heightCenter);
  sf::Vector2f s(windowSize.x, heightSide);
  auto cs = s - c;

  // Calculate normals.
  sf::Vector2f ns(-cs.y, cs.x);
  sf::Vector2f nc(0, -1);

  // The intersection is the point on the other side of the planet
  // in relation to c.
  auto r = calculateIntersection(c, s, nc, ns);
  earthRadius = (r.y + heightCenter) / 2;
  earthPosition.y = windowSize.y + heightCenter + earthRadius;
  earthPosition.x = windowSize.x / 2.f;
}
