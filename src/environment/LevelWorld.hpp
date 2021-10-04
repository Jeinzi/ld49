#ifndef _LEVELWORLD_HPP
#define _LEVELWORLD_HPP

#include "World.hpp"
#include "Plane.hpp"
#include "Cloud.hpp"


class LevelWorld : public World {
  public:
    LevelWorld();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool update(sf::Time time) override;
    void resize(sf::Vector2u const windowSize) override;
    void keyPressed(sf::Event e);

  protected:
    void calculateEarthCenter(sf::Vector2u const windowSize) override;

    Plane plane;
    std::vector<Cloud> clouds;
};

#endif
