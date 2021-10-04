#include "LevelWorld.hpp"
#include <iostream>


LevelWorld::LevelWorld() {
  skyColor = sf::Color(50, 110, 250, 255);
}


void LevelWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  World::draw(target, states);
  plane.draw(target, states);
}


void LevelWorld::update(sf::Time time) {
  World::update(time);
  earthShape.setOrigin(earthRadius, earthRadius);
  plane.update(time);
}


void LevelWorld::calculateEarthCenter(sf::Vector2u const windowSize) {
  auto w = windowSize.x;
  auto h = windowSize.y;
  float heightSide = 0.15 * h;
  float heightCenter = 0.2 * h;
  
  // Define two points and a vector connecting them.
  sf::Vector2f c(w / 2.f, h - heightCenter);
  sf::Vector2f s(w, h - heightSide);
  auto cs = s - c;

  std::cout << "c.x: " << c.x << std::endl;
  std::cout << "c.y: " << c.y << std::endl;
  std::cout << "s.x: " << s.x << std::endl;
  std::cout << "s.y: " << s.y << std::endl;


  // Calculate normals.
  sf::Vector2f ns(-cs.y, cs.x);
  sf::Vector2f nc(0, 1);

  // The intersection is the point on the other side of the planet
  // in relation to c.
  auto r = calculateIntersection(c, s, nc, ns);
  earthRadius = (r.y + heightCenter) / 2;
  earthPosition.y = h + earthRadius - heightCenter;
  earthPosition.x = w / 2.f;

  std::cout << "r.x: " << r.x << std::endl;
  std::cout << "r.y: " << r.y << std::endl;
  std::cout << "earthRadius: " << earthRadius << std::endl;
  std::cout << "earthPosition.x: " << earthPosition.x << std::endl;
  std::cout << "earthPosition.y: " << earthPosition.y << std::endl;
}
