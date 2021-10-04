#ifndef _BAR_HPP
#define _BAR_HPP

#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>


class Bar : public sf::Drawable {
  public:
    Bar();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time);
    void setFillColor(sf::Color const c);
    void setOutlineColor(sf::Color const c);
    void setOutlineThickness(unsigned int const t);
    void setMaxValue(float const v);
    void setValue(float const v);
    void setPosition(sf::Vector2f const p);
    void setSize(sf::Vector2f const s);
  
  private:
    float maxValue;
    float value;
    sf::RectangleShape outline;
    sf::RectangleShape fill;
};

#endif
