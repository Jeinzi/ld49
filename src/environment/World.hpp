#ifndef _WORLD_HPP
#define _WORLD_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Time.hpp>


class World : public sf::Drawable {
  public:
    World();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time);
    //void keyPressed(sf::Event event);
    //void mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates);

  private:
    sf::Color skyColor;
};

#endif
