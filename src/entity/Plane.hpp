#ifndef _PLANE_HPP
#define _PLANE_HPP

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
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
    bool update(sf::Time time);
    void resize(sf::Vector2u const windowSize);
    void keyPressed(sf::Event e);
    sf::FloatRect getBounds() const;
    void addFuel(float amount);

  private:
    bool doExplode = false;
    bool hasExplosionSoundPlayed = false;
    float angle = 0;
    float lastAngleChange = 0;
    float fuelConsumption;
    float totalTime = 0;
    float vMax;
    float stability;
    float stabilityChange;
    StaticStability staticStability;
    DynamicStability dynamicStability;
    sf::Vector2f position;
    sf::Vector2f v;
    sf::Vector2u windowSize;
    sf::Sprite planeSprite;
    sf::Text stabilityText;
    Animation explosion;
    sf::Sound explosionSound;
    Bar fuelBar;
    sf::Sound fuelSound;
};

#endif
