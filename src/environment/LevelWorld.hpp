#ifndef _LEVELWORLD_HPP
#define _LEVELWORLD_HPP

#include "World.hpp"
#include "Plane.hpp"


class LevelWorld : public World {
  public:
    LevelWorld();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time) override;
    void resize(sf::Vector2u const windowSize) override;

  protected:
    void calculateEarthCenter(sf::Vector2u const windowSize) override;

    Plane plane;
};

#endif
