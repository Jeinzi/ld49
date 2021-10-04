#include "Bar.hpp"


Bar::Bar(float value, float maxValue)
  : maxValue(maxValue), value(value)
{
  //fill.setOutlineThickness(0);
  setFillColor(sf::Color::Red);
  setOutlineColor(sf::Color::Black);
  outline.setFillColor(sf::Color::Transparent);
  setOutlineThickness(2);
  calculateSize();
}


void Bar::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(fill, states);
  target.draw(outline, states);
}


void Bar::update(sf::Time time) {
  
}


void Bar::setFillColor(sf::Color const c) {
  fill.setFillColor(c);
}


void Bar::setOutlineColor(sf::Color const c) {
  outline.setOutlineColor(c);
}


void Bar::setOutlineThickness(unsigned int const t) {
  outline.setOutlineThickness(t);
}

void Bar::setMaxValue(float const v) {

}


void Bar::setValue(float const v) {
  value = v;
  if (value < 0) {
    value = 0;
  }
  else if(value > maxValue) {
    value = maxValue;
  }

  calculateSize();
}


float Bar::getValue() {
  return value;
}


void Bar::setPosition(sf::Vector2f const p) {
  outline.setPosition(p);
  fill.setPosition(p);
}


void Bar::setSize(sf::Vector2f const s) {
  outline.setSize(s);
  auto fillSize = fill.getSize();
  fillSize.y = s.y;
  fillSize.x = 0.7 * s.x;
  fill.setSize(fillSize);
}


void Bar::calculateSize() {
  auto fs = fill.getSize();
  fs.x = outline.getSize().x / maxValue * value;
  fill.setSize(fs);
}
