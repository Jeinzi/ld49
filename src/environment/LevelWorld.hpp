#ifndef _LEVELWORLD_HPP
#define _LEVELWORLD_HPP

#include "World.hpp"


class LevelWorld : public World {
  public:
    LevelWorld();
    void calculateEarthCenter(sf::Vector2u const windowSize);
    
};

#endif
