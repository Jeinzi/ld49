#ifndef _BAR_HPP
#define _BAR_HPP

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


class Bar : public sf::Drawable {
  public:
    Bar(float value = 0, float maxValue = 100);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Time time);
    void setFillColor(sf::Color const c);
    void setOutlineColor(sf::Color const c);
    void setOutlineThickness(unsigned int const t);
    void setMaxValue(float const v);
    void setValue(float const v);
    float getValue();
    void setPosition(sf::Vector2f const p);
    void setSize(sf::Vector2f const s);
  
  private:
    void calculateSize();

    float maxValue;
    float value;
    sf::RectangleShape outline;
    sf::RectangleShape fill;
};

#endif
