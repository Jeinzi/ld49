#ifndef _CLOUD_HPP
#define _CLOUD_HPP

#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Resources.hpp"


class Cloud : public sf::Drawable {
  public:
    Cloud(sf::Vector2f const& pos, sf::Vector2f const& v);
    void update(sf::Time time);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool isVisible(/* sf::Vector2f windowSize */) const;

  private:
    sf::Vector2f v;
    sf::Vector2f pos;
    sf::Sprite sprite;
};


#endif
