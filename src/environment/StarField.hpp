#ifndef _STARFIELD_HPP
#define _STARFIELD_HPP

#include <vector>
#include <cstdlib>
#include "SFML/System.hpp"
#include <SFML/Graphics.hpp>


struct Star {
  sf::Vector2f position;
  sf::Vector2f size;
  uint8_t brightness;
};


class StarField : public sf::Drawable{
  public:
    StarField(unsigned int n);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time);

  private:
    std::vector<Star> stars;
};


#endif
