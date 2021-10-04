#ifndef _JERRYCAN_HPP
#define _JERRYCAN_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "Animation.hpp"


class Jerrycan : public sf::Drawable {
  public:
    Jerrycan();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time);
  
  private:
    sf::Vector2f position;
    Animation animationDefault;
    std::reference_wrapper<Animation> currentAnimation;
};

#endif
