#include <SFML/Window/ContextSettings.hpp>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <SFML/Graphics.hpp>

#include "Resources.hpp"
#include "GameStateManager.hpp"

#include <iostream>



int main() {
  srand(time(NULL));
  auto screen = sf::VideoMode::getDesktopMode();
  auto videoMode = sf::VideoMode(screen.width, screen.height);
  sf::RenderWindow window(videoMode, "Maybe a Game", sf::Style::Fullscreen, sf::ContextSettings(0, 0, 1));
  window.setVerticalSyncEnabled(true);
  window.setActive(false);

  Resources::load();

  sf::Vector2f viewSize(screen.width, screen.height);
  sf::Vector2f center(screen.width / 2.f, screen.height / 2.f);
  sf::View view(center, viewSize);
  window.setView(view);
  GameStateManager gsm;

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      else if (event.type == sf::Event::KeyPressed) {
        gsm.keyPressed(event);
      }
      else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i coordinates = { event.mouseButton.x, event.mouseButton.y };
        gsm.mouseButtonPressed(event, window.mapPixelToCoords(coordinates));
      }
      else if (event.type == sf::Event::MouseWheelScrolled) {
        gsm.mouseWheelMoved(event);
      }
      else if (event.type == sf::Event::Resized)
      {
        // Adapt view to new window size.
        auto windowSize = window.getSize();
        sf::Vector2f viewSize(windowSize.x, windowSize.y);
        sf::Vector2f center(windowSize.x / 2.f, windowSize.y / 2.f);
        sf::View view(center, viewSize);
        window.setView(view);

        // Pass resize information to GSM.
        gsm.resize(windowSize);
      }
    }
    if (!gsm.update(clock.restart())) {
      window.close();
    }
    window.draw(gsm);
    window.display();
  }

  return EXIT_SUCCESS;
}
