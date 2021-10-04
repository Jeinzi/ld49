#include "Plane.hpp"


Plane::Plane()
  : vMax(150), position(0, 300), v(0, 0), planeSprite(Resources::getTexture("airship"))
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
  //auto modifiedPosition = position;
  //modifiedPosition.y += 100 * std::sin(totalTime);

  //angle = std::cos(totalTime);
  unsigned int const q = 100;
  //angle += static_cast<float>((rand() % (2*q)) - q) / q / 360 * 2 * M_PI;
  planeSprite.setRotation(angle / 2 / M_PI * 360);

  float da;
  float k1 = 0.01;
  float k2 = 0.6;

  // Static stability.
  //da = -k2 * angle;

  // Static instability.
  da = k2 * angle * time.asSeconds();

  // Dynamic instability.
  //auto dda = da - lastAngleChange;
  //da = -k1 * dda - k2 * da;

  angle += da;

  v.y = vMax * std::sin(angle);
  v.x = vMax * std::sin(angle);
  position += time.asSeconds() * v;
  planeSprite.setPosition(position);

}


void Plane::resize(sf::Vector2u const windowSize) {
  position.x = windowSize.x / 2.f;
}


void Plane::keyPressed(sf::Event e) {
  float da = 3;
  if (e.key.code == sf::Keyboard::Up) {
    angle -= da / 360 * 2 * M_PI;
  }
  else if (e.key.code == sf::Keyboard::Down) {
    angle += da / 360 * 2 * M_PI;
  }
}
