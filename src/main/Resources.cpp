#include "Resources.hpp"
#include <iostream>


bool Resources::isLoaded = false;
std::unordered_map<std::string, sf::Font> Resources::fonts;
std::unordered_map<std::string, std::string> Resources::paths;
std::unordered_map<std::string, std::string> Resources::texts;
std::unordered_map<std::string, sf::Texture> Resources::textures;
std::unordered_map<std::string, sf::SoundBuffer> Resources::soundEffects;
std::unordered_map<std::string, sf::Music> Resources::music;

void Resources::load() {
  isLoaded = true;

  // Fonts.
  fonts["8bit"].loadFromFile("res/font/PressStart2P-Regular.ttf");

  // Paths.
  paths["airship_properties"] = "res/sprites/airship.json";
  paths["lang_en_US"] = "res/lang/en_US.json";

  // Texts.
  loadLanguage("lang_en_US");
  
  // Textures.
  textures["airship"].loadFromFile("res/sprites/airship.png");

  // Sound effects.
  //soundEffects["jump0"].loadFromFile("res/sfx/jump0.ogg");
  
  // Music.
  music["misty"].openFromFile("res/music/Misty.ogg");
}


void Resources::loadLanguage(std::string const& id) {
  char readBuffer[65536];
  auto langPath = Resources::getPath("lang_en_US");
  FILE* propertyFile = fopen(langPath.c_str(), "r");
  rapidjson::FileReadStream propertyStream(propertyFile, readBuffer, sizeof(readBuffer));

  rapidjson::Document doc;
  doc.ParseStream(propertyStream);
  fclose(propertyFile);

  if (doc.HasParseError()) {
    throw; // @todo
  }

  auto obj = doc.GetObject();
  for (auto it = obj.MemberBegin(); it != obj.MemberEnd(); ++it) {
    //const rapidjson::Value& objName = obj[it->name.GetString()];

    if (!it->value.IsString()) {
      // Todo error
    }

    texts[it->name.GetString()] = it->value.GetString();
  }
}


sf::Font const& Resources::getFont(std::string const& id) {
  if (!isLoaded) {
    load();
  }
  return fonts.at(id);
}


std::string Resources::getPath(std::string const& id) {
  if (!isLoaded) {
    load();
  }
  return paths.at(id);
}


sf::Texture const& Resources::getTexture(std::string const& id) {
  if (!isLoaded) {
    load();
  }
  return textures.at(id);
}


sf::SoundBuffer const& Resources::getSoundBuffer(std::string const& id) {
  if (!isLoaded) {
    load();
  }
  return soundEffects.at(id);
}

sf::Music& Resources::getMusic(std::string const& id) {
  if (!isLoaded) {
    load();
  }
  return music.at(id);
}


std::string Resources::getText(std::string const& id) {
  if (!isLoaded) {
    load();
  }
  return texts.at(id);
}
