#include "Plane.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>


Plane::Plane()
  : position(0, 500),
    animationDefault("airship", {1}),
    currentAnimation(animationDefault)
{
  currentAnimation.get().setHeight(50);
  fuelBar.setPosition({10, 10});
  fuelBar.setSize({200, 20});
  fuelBar.setOutlineThickness(3);
  fuelBar.setFillColor(sf::Color::Yellow);
}


void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  currentAnimation.get().draw(target, states);

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
  currentAnimation.get().update(time);
  auto modifiedPosition = position;
  modifiedPosition.y += 100 * std::sin(totalTime);
  currentAnimation.get().setPosition(modifiedPosition);
}
