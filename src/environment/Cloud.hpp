#ifndef _CLOUD_HPP
#define _CLOUD_HPP

#include <cmath>
#include <string>
#include <cstdlib>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Resources.hpp"


class Cloud : public sf::Drawable {
  public:
    Cloud();
    void update(sf::Time time);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void resize(sf::Vector2u const windowSize);
    bool isVisible() const;

  private:
    static sf::Vector2u windowSize;
    sf::Vector2f v;
    sf::Vector2f unscaledPos;
    sf::Sprite sprite;
};

#endif
