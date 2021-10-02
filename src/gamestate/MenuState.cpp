#include "MenuState.hpp"
#include "Resources.hpp"


MenuState::MenuState(GameStateManager& gsm, World& world)
  : GameState(gsm), zoom(1), selectedItem(0),  world(world),
     menuEntryIds({"menu_start", "menu_options", "menu_highscore", "menu_about", "menu_quit"})
{

}

MenuState::~MenuState() {}


void MenuState::init() {
  sf::Music& music = Resources::getMusic("misty");
  music.setLoop(true);
  music.setVolume(75);
  music.play();
}


void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  //auto view = target.getView();
  //view.zoom(zoom);
  //zoom = 1;
  //target.setView(view);

  auto view = target.getView();
  target.setView(target.getDefaultView());

  // Get screen size.
  auto w = target.getSize().x;
  auto h = target.getSize().y;

  // Draw world.
  target.draw(world, states);

  // Game title.
  sf::Text title;
  sf::Vector2f pos(0.05*w, 0.1*h);
  title.setPosition(pos);
  title.setFont(Resources::getFont("8bit"));
  title.setString(Resources::getText("game_title"));
  title.setCharacterSize(90);
  title.setFillColor(sf::Color::White);
  title.setStyle(sf::Text::Bold | sf::Text::Underlined);
  auto titleSize = title.getLocalBounds();
  target.draw(title, states);

  // Menu items
  pos.y += titleSize.height + 0.1 * h;
  
  sf::Text menuEntry;
  menuEntry.setFont(Resources::getFont("8bit"));
  menuEntry.setCharacterSize(20);
  menuEntry.setFillColor(sf::Color::White);

  unsigned int i = 0;
  for (auto const& id : menuEntryIds) {
    menuEntry.setString(Resources::getText(id));
    menuEntry.setPosition(pos);
    if (i == selectedItem) {
      menuEntry.setStyle(sf::Text::Underlined);
    }
    else {
      menuEntry.setStyle(sf::Text::Regular);
    }
    
    target.draw(menuEntry, states);

    ++i;
    pos.y += 40;
  }

  target.setView(view);
}


void MenuState::update(sf::Time time) {
  //player.update(time);
}


void MenuState::keyPressed(sf::Event event) {
  auto nEntries = menuEntryIds.size();

  // Change selected entry.
  if (event.key.code == sf::Keyboard::Down ||
      event.key.code == sf::Keyboard::S)
  {
    ++selectedItem;
    if (selectedItem >= nEntries) {
      selectedItem = 0;
    }
  }
  else if (event.key.code == sf::Keyboard::Up ||
           event.key.code == sf::Keyboard::W)
  {
    --selectedItem;
    if (selectedItem >= nEntries) {
      selectedItem = nEntries - 1;
    }
  }

  // Confirm entry.
  if (event.key.code == sf::Keyboard::Enter) {
    if (menuEntryIds[selectedItem] == "menu_quit") {
      gsm.exit();
    }
    else if (menuEntryIds[selectedItem] == "menu_start") {
      gsm.changeState(GameStateManager::State::Level);
    }
    else if (menuEntryIds[selectedItem] == "menu_options") {
      Resources::loadLanguage("lang_de_DE");
    }
  }
}


void MenuState::mouseButtonPressed(sf::Event event, sf::Vector2f worldCoordinates) {
  //player.mouseButtonPressed(event, worldCoordinates);
}
