#include "LevelWorld.hpp"


LevelWorld::LevelWorld() {
  skyColor = sf::Color(50, 110, 250, 255);
  timeMins = 0;
  dayLengthMins = 10;

  for (int i = 0; i < 7; ++i) {
    clouds.emplace_back();
  }
}


void LevelWorld::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  World::draw(target, states);
  for (auto const& c: clouds) {
    c.draw(target, states);
  }

  plane.draw(target, states);
}


void LevelWorld::update(sf::Time time) {
  World::update(time);
  earthShape.setOrigin(earthRadius, earthRadius);
  plane.update(time);
  
  //Clouds.
  for (size_t i = 0; i < clouds.size(); ++i) {
    auto& c = clouds[i];
    c.update(time);
    if (!c.isVisible()) {
      c = Cloud();
    }
  }
}


void LevelWorld::resize(sf::Vector2u const windowSize) {
  World::resize(windowSize);
  plane.resize(windowSize);
  for (auto& c: clouds) {
    c.resize(windowSize);
  }
}


void LevelWorld::calculateEarthCenter(sf::Vector2u const windowSize) {
  auto w = windowSize.x;
  auto h = windowSize.y;
  float heightSide = 0.13 * h;
  float heightCenter = 0.2 * h;
  
  // Define two points and a vector connecting them.
  sf::Vector2f c(w / 2.f, h - heightCenter);
  sf::Vector2f s(w, h - heightSide);
  auto cs = s - c;

  // Calculate normals.
  sf::Vector2f ns(-cs.y, cs.x);
  sf::Vector2f nc(0, 1);

  // The intersection is the point on the other side of the planet
  // in relation to c.
  auto r = calculateIntersection(c, s, nc, ns);
  earthRadius = (r.y + heightCenter) / 2;
  earthPosition.y = h + earthRadius - heightCenter;
  earthPosition.x = w / 2.f;
}
