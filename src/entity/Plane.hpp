#ifndef _PLANE_HPP
#define _PLANE_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

#include "Bar.hpp"
#include "Animation.hpp"


enum class StaticStability {
  Stable,
  Neutral,
  Unstable
};


enum class DynamicStability {
  Stable,
  Neutral,
  Unstable
};


class Plane : public sf::Drawable {
  public:
    Plane();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time);

  private:
    float angle = 0;
    float fuel;
    float maxFuel;
    float fuelConsumption;
    float totalTime = 0;
    StaticStability staticStability;
    DynamicStability dynamicStability;
    sf::Vector2f position;
    Animation animationDefault;
    std::reference_wrapper<Animation> currentAnimation;
    Bar fuelBar;
};

#endif
