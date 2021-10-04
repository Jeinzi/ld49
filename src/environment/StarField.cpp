#include "StarField.hpp"


StarField::StarField(unsigned int n) {
  stars.reserve(n);
  auto rp = []() {
    return static_cast<float>(rand() % 1000) / 1000.f;
  };

  for (unsigned int i = 0; i < n; ++i) {
    sf::Vector2f position {rp(), rp()};
    float s = (rand() % 4) + 1;
    sf::Vector2f size {s, s};
    uint8_t brightness = rand() % 255;
    stars.push_back({position, size, brightness});
  }
}


void StarField::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // ToDo Performance. Don't use shapes, use vertices
  // and only regenerate on resize.
  for (auto const& s: stars) {
    sf::RectangleShape rectangle;
    rectangle.setSize(s.size);
    
    auto b = s.brightness;
    rectangle.setFillColor(sf::Color(b, b, b));

    auto w = target.getSize().x;
    auto h = target.getSize().y;
    sf::Vector2f position(s.position.x * w, s.position.y * h);
    rectangle.setPosition(position);

    target.draw(rectangle, states);
  }
}


void StarField::update(sf::Time time) {

}
