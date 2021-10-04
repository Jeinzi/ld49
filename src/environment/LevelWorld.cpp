#include "LevelWorld.hpp"
#include <SFML/Graphics/Color.hpp>
#include <cmath>


LevelWorld::LevelWorld() {
  skyColor = sf::Color(50, 110, 250, 255);
  timeMins = 0;
  dayLengthMins = 5;

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


bool LevelWorld::update(sf::Time time) {
  sf::Color skyColorDay(50, 110, 250, 255);
  float arg = timeMins / dayLengthMins * 2 * M_PI + M_PI / 12 * 7;
  float f = 1.3 * (-std::cos(arg) + 0.5);
  f = f > 1 ? 1 : f;
  f = f < 0 ? 0 : f;
  float r = skyColorDay.g * f;
  float g = skyColorDay.g * f;
  float b = skyColorDay.b * f;
  skyColor = sf::Color(r, g, b);
  starField.setCutoffBrightness(f);
  World::update(time);
  earthShape.setOrigin(earthRadius, earthRadius);
  
  //Clouds.
  for (size_t i = 0; i < clouds.size(); ++i) {
    auto& c = clouds[i];
    c.update(time);
    if (!c.isVisible()) {
      c = Cloud();
    }
  }

  return plane.update(time);
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


void LevelWorld::keyPressed(sf::Event e) {
  plane.keyPressed(e);
}
