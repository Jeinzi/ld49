#ifndef _WORLD_HPP
#define _WORLD_HPP

#include <cmath>
#include <SFML/Graphics.hpp>

#include "StarField.hpp"


class World : public sf::Drawable {
  public:
    World();

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    virtual void update(sf::Time time);
    void resize(sf::Vector2u const windowSize);
    //void setDayLength(float minutes);
    //void keyPressed(sf::Event event);
    //void mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates);

  protected:
    float dayLengthMins;
    float timeMins;
    sf::Color skyColor;
    sf::Vector2f earthPosition;
    float earthRadius;
    StarField starField;
    sf::CircleShape earthShape;

    virtual void calculateEarthCenter(sf::Vector2u const windowSize) = 0;
    sf::Vector2f calculateIntersection(sf::Vector2f const p1,
                                       sf::Vector2f const p2,
                                       sf::Vector2f const v1,
                                       sf::Vector2f const v2) const;
};

#endif
