#ifndef _MENUWORLD_CPP
#define _MENUWORLD_CPP

#include "World.hpp"


class MenuWorld : public World {
  public:
    MenuWorld(sf::Vector2u const& windowSize);
    //void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool update(sf::Time time) override;
    //void resize(sf::Vector2u const windowSize) override;
  
  protected:
    void calculateEarthCenter(sf::Vector2u const windowSize) override;
    
};

#endif
