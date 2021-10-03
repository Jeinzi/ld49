#ifndef _WORLD_HPP
#define _WORLD_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

#include "StarField.hpp"


class World : public sf::Drawable {
  public:
    World();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time);
    void resize(sf::Vector2u const windowSize);
    //void keyPressed(sf::Event event);
    //void mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates);

  private:
    float dayLengthMins;
    float timeMins;
    sf::Color skyColor;
    sf::Vector2f earthPosition;
    float earthRadius;
    StarField starField;

    void calculateEarthCenter(sf::Vector2u const windowSize);
    sf::Vector2f calculateIntersection(sf::Vector2f const p1,
                                       sf::Vector2f const p2,
                                       sf::Vector2f const v1,
                                       sf::Vector2f const v2) const;
};

#endif
