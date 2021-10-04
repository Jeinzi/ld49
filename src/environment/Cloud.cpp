#include "Cloud.hpp"


sf::Vector2u Cloud::windowSize = {1920, 1080};

Cloud::Cloud() {
  // Choose cloud.
  unsigned char const nCloudVariants = 4;
  unsigned char cloudId = rand() % nCloudVariants;
  std::string spriteName = "cloud-" + std::to_string(cloudId);
  sprite = sf::Sprite(Resources::getTexture(spriteName));

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

  // Random size.
  float s = static_cast<float>(rand() % 50 + 50) / 200.f;
  sprite.setScale(s, s);
}


void Cloud::update(sf::Time time) {
  unscaledPos += v * time.asSeconds();
  sprite.setPosition({unscaledPos.x * windowSize.x, unscaledPos.y});
}


void Cloud::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite, states);
}


void Cloud::resize(sf::Vector2u const windowSize) {
  this->windowSize = windowSize;
}


bool Cloud::isVisible() const {
  auto b = sprite.getGlobalBounds();

  if (b.left + b.width < 0) {
    return false;
  }
  return true;
}
