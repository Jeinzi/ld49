#ifndef _JERRYCAN_HPP
#define _JERRYCAN_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "Animation.hpp"


class Jerrycan : public sf::Drawable {
  public:
    Jerrycan();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time);
    void resize(sf::Vector2u const windowSize);
    bool isVisible() const;
    sf::FloatRect getBounds() const;
  
  private:
    static sf::Vector2u windowSize;
    sf::Vector2f v;
    sf::Vector2f unscaledPos;
    sf::Sprite sprite;
};

#endif
