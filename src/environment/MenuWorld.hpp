#ifndef _MENUWORLD_CPP
#define _MENUWORLD_CPP

#include "World.hpp"


class MenuWorld : public World {
  public:
    //MenuWorld();
    void calculateEarthCenter(sf::Vector2u const windowSize);
    
};

#endif
