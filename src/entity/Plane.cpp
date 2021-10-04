#include "Plane.hpp"
#include "Resources.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Text.hpp>
#include <cmath>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>


Plane::Plane()
  : fuelConsumption(1000/60.f),
    vMax(150), stability(-1), stabilityChange(1/60.f),
    position(0, 300), v(0, 0), planeSprite(Resources::getTexture("airship")),
    explosion("explosion", {50}), explosionSound(Resources::getSoundBuffer("explosion")),
    fuelBar(300, 1000)
{
  fuelBar.setPosition({10, 10});
  fuelBar.setSize({200, 20});
  fuelBar.setOutlineThickness(3);
  fuelBar.setFillColor(sf::Color::Yellow);

  stabilityText.setPosition({10, 40});
  stabilityText.setFont(Resources::getFont("8bit"));
  stabilityText.setCharacterSize(10);
  stabilityText.setFillColor(sf::Color::White);

  float const s = 0.05;
  planeSprite.setScale(s, s);
  auto b = planeSprite.getLocalBounds();
  auto ox = b.width / 2;
  auto oy = b.height / 2;
  planeSprite.setOrigin(ox, oy);

  explosion.setIterations(1);
}


void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (doExplode) {
    explosion.draw(target, states);
  }
  else {
    target.draw(planeSprite, states);
  }

  // Change view for overlays.
  auto oldView = target.getView();
  auto windowSize = target.getSize();
  sf::Vector2f viewSize(windowSize.x, windowSize.y);
  sf::Vector2f center(windowSize.x / 2.f, windowSize.y / 2.f);
  sf::View view(center, viewSize);
  target.setView(view);

  // Fuel meter.
  fuelBar.draw(target, states);

  // Stability.
  target.draw(stabilityText, states);


  target.setView(oldView);
}


bool Plane::update(sf::Time time) {
  totalTime += time.asSeconds();
  //auto modifiedPosition = position;
  //modifiedPosition.y += 100 * std::sin(totalTime);

  //angle = std::cos(totalTime);
  unsigned int const q = 100;
  //angle += static_cast<float>((rand() % (2*q)) - q) / q / 360 * 2 * M_PI;
  planeSprite.setRotation(angle / 2 / M_PI * 360);

  // Fuel.
  auto fuel = fuelBar.getValue();
  fuel -= fuelConsumption * time.asSeconds();
  fuelBar.setValue(fuel);
  //fuelBar.update(time);



  // Static stability.
  float da;
  //da = -k2 * angle * time.asSeconds();
  stability += stabilityChange * time.asSeconds();
  std::wstringstream ss;
  ss.precision(1);
  ss << Resources::getText("stability") << ": "
     << stability;
  stabilityText.setString(ss.str());

  // Static instability.
  da = stability * angle * time.asSeconds();
  //std::cout << da / time.asSeconds() << std::endl;

  // Dynamic instability.
  //auto dda = da - lastAngleChange;
  //da = -k1 * dda - k2 * da;

  angle += da;


  // Explosion triggers.
  // ToDo simplify
  if (std::abs(da / time.asSeconds()) > 2) {
    doExplode = true;
  }
  if (position.y > windowSize.y * (1 - 0.14)) {
    doExplode = true;
  }
  if (fuelBar.getValue() <= 0) {
    //v.y = -10;
    //angle = 30.f / 360 * 2 * M_PI;
    doExplode = true;
  }

  // Explosion action.
  if (doExplode) {
    explosion.setPosition(position, true);
    explosion.update(time);

    auto& music = Resources::getMusic("misty");
    if (music.getStatus() == sf::Music::Status::Playing) {
      music.pause();
    }

    if (hasExplosionSoundPlayed &&
        explosionSound.getStatus() != sf::Sound::Status::Playing)
    {
      return false;
    }

    if (explosionSound.getStatus() != sf::Sound::Status::Playing) {
      explosionSound.play();
      hasExplosionSoundPlayed = true;
    }
  }

  
  // Movement.
  if (!doExplode) {
    v.y = vMax * std::sin(angle);
    v.x = vMax * std::sin(angle);
    position += time.asSeconds() * v;
    planeSprite.setPosition(position);
  }

  return true;
}


void Plane::resize(sf::Vector2u const windowSize) {
  position.x = windowSize.x / 2.f;
  this->windowSize = windowSize;
}


void Plane::keyPressed(sf::Event e) {
  float da = 3;
  if (e.key.code == sf::Keyboard::Up) {
    angle -= da / 360 * 2 * M_PI;
  }
  else if (e.key.code == sf::Keyboard::Down) {
    angle += da / 360 * 2 * M_PI;
  }
}
