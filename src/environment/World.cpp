#include "World.hpp"


World::World()
  : skyColor(50, 110, 250, 255)
{
  
}


void World::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.clear(skyColor);
}
