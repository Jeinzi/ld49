#ifndef _LEVELWORLD_HPP
#define _LEVELWORLD_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "World.hpp"
#include "Plane.hpp"
#include "Cloud.hpp"
#include "Jerrycan.hpp"


class LevelWorld : public World {
  public:
    LevelWorld();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool update(sf::Time time) override;
    void resize(sf::Vector2u const windowSize) override;
    void keyPressed(sf::Event e);

  protected:
    void calculateEarthCenter(sf::Vector2u const windowSize) override;

    sf::Time totalTime;
    sf::Text deathText;
    Plane plane;
    std::vector<Cloud> clouds;
    std::vector<Jerrycan> jerrycans;
};

#endif
