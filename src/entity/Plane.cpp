#include "Plane.hpp"
#include "Resources.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <cmath>
#include <iostream>
#include <math.h>


Plane::Plane()
  : vMax(150), position(0, 300), v(0, 0), planeSprite(Resources::getTexture("airship")),
    explosion("explosion", {50}), explosionSound(Resources::getSoundBuffer("explosion"))
{
  fuelBar.setPosition({10, 10});
  fuelBar.setSize({200, 20});
  fuelBar.setOutlineThickness(3);
  fuelBar.setFillColor(sf::Color::Yellow);

  float const s = 0.05;
  planeSprite.setScale(s, s);
  auto b = planeSprite.getLocalBounds();
  auto ox = b.width / 2;
  auto oy = b.height / 2;
  planeSprite.setOrigin(ox, oy);

  explosion.setIterations(1);
  //explosionSound.setLoop(false);
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

  float da;
  float k1 = 0.01;
  float k2 = 0.6;

  // Static stability.
  //da = -k2 * angle * time.asSeconds();

  // Static instability.
  da = k2 * angle * time.asSeconds();
  //std::cout << da / time.asSeconds() << std::endl;

  // Dynamic instability.
  //auto dda = da - lastAngleChange;
  //da = -k1 * dda - k2 * da;

  angle += da;


  // Explosion triggers.
  if (std::abs(da / time.asSeconds()) > 2) {
    doExplode = true;
  }
  if (position.y > windowSize.y * (1 - 0.14)) {
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
