#include "Plane.hpp"
#include "Resources.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>


Plane::Plane()
  : position(0, 300), planeSprite(Resources::getTexture("airship"))
{
  fuelBar.setPosition({10, 10});
  fuelBar.setSize({200, 20});
  fuelBar.setOutlineThickness(3);
  fuelBar.setFillColor(sf::Color::Yellow);

  float const s = 0.05;
  planeSprite.setScale(s, s);
  auto b = planeSprite.getLocalBounds();
  auto ox = b.width / 2;
  auto oy = b.height / 2;
  planeSprite.setOrigin(ox, oy);
}


void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(planeSprite, states);

  // Change view for overlays.
  auto oldView = target.getView();
  auto windowSize = target.getSize();
  sf::Vector2f viewSize(windowSize.x, windowSize.y);
  sf::Vector2f center(windowSize.x / 2.f, windowSize.y / 2.f);
  sf::View view(center, viewSize);
  target.setView(view);

  // Fuel meter.
  fuelBar.draw(target, states);

  target.setView(oldView);
}


void Plane::update(sf::Time time) {
  totalTime += time.asSeconds();
  auto modifiedPosition = position;
  modifiedPosition.y += 100 * std::sin(totalTime);
  planeSprite.setPosition(modifiedPosition);

  angle = std::cos(totalTime);
  planeSprite.setRotation(angle / 2 / M_PI * 360);
}


void Plane::resize(sf::Vector2u const windowSize) {
  position.x = windowSize.x / 2.f;
}
