#include "Jerrycan.hpp"


sf::Vector2u Jerrycan::windowSize = {1920, 1080};

Jerrycan::Jerrycan()
  : sprite(Resources::getTexture("jerrycan"))
{
  float s = 0.3;
  sprite.setScale(s, s);

  // Random position.
  unsigned int q = 1000;
  unscaledPos.x = static_cast<float>(rand() % q) / q + 2;
  unscaledPos.y = rand() % 500;
  sprite.setPosition({unscaledPos.x * windowSize.x, unscaledPos.y});

  // Random speed.
  unsigned int const screenTimeMin = 3;
  unsigned int const screenTimeMax = 6;
  float screenTime = screenTimeMin + rand() % (screenTimeMax-screenTimeMin);
  v = sf::Vector2f(-1 / screenTime, 0);
}

void Jerrycan::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite, states);
}


void Jerrycan::update(sf::Time time) {
  unscaledPos += v * time.asSeconds();
  sprite.setPosition({unscaledPos.x * windowSize.x, unscaledPos.y});
}


void Jerrycan::resize(sf::Vector2u const windowSize) {
  this->windowSize = windowSize;
}


bool Jerrycan::isVisible() const {
  auto b = sprite.getGlobalBounds();

  if (b.left + b.width < 0) {
    return false;
  }
  return true;
}

sf::FloatRect Jerrycan::getBounds() const {
  return sprite.getGlobalBounds();
}
