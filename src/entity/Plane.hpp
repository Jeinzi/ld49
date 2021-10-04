#ifndef _PLANE_HPP
#define _PLANE_HPP

#include <cmath>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Bar.hpp"
#include "Animation.hpp"
#include "Resources.hpp"


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
    void resize(sf::Vector2u const windowSize);
    void keyPressed(sf::Event e);

  private:
    float angle = 0;
    float lastAngleChange = 0;
    float fuel;
    float maxFuel;
    float fuelConsumption;
    float totalTime = 0;
    float vMax;
    StaticStability staticStability;
    DynamicStability dynamicStability;
    sf::Vector2f position;
    sf::Vector2f v;
    sf::Sprite planeSprite;
    Bar fuelBar;
};

#endif
