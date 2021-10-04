#include "Cloud.hpp"
#include <SFML/System/Vector2.hpp>


Cloud::Cloud(sf::Vector2f const& pos, sf::Vector2f const& v)
  : v(v), pos(pos)
{
  unsigned char const nCloudVariants = 4;
  unsigned char cloudId = rand() % nCloudVariants;
  std::string spriteName = "cloud-" + std::to_string(cloudId);
  sprite = sf::Sprite(Resources::getTexture(spriteName));

  float s = static_cast<float>(rand() % 50 + 50) / 100.f;
  sprite.setScale(s, s);
}


void Cloud::update(sf::Time time) {
  pos += v * time.asSeconds();
  sprite.setPosition(pos);
}


bool Cloud::isVisible(/* sf::Vector2f windowSize */) const {
  auto b = sprite.getGlobalBounds();

  if (b.left + b.width < 0) {
    return false;
  }
/*   if (b.top + b.height < 0) {
    return false;
  }
  if (b.top > windowSize.y) {
    return false;
  } */
  return true;
}


void Cloud::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite, states);
}
