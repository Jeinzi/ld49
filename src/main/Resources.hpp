#ifndef _RESOURCES_HPP
#define _RESOURCES_HPP

#include <string>
#include <codecvt>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>


class TileSet;

class Resources {
  public:
    Resources() = delete;
    static void load();
    static void loadLanguage(std::string const& id);
    static sf::Font const& getFont(std::string const& id);
    static std::string getPath(std::string const& id);
    static std::wstring getText(std::string const& id);
    static sf::Texture const& getTexture(std::string const& id);
    static sf::SoundBuffer const& getSoundBuffer(std::string const& id);
    static sf::Music& getMusic(std::string const& id);


  private:

    static bool isLoaded;
    static std::unordered_map<std::string, sf::Font> fonts;
    static std::unordered_map<std::string, std::string> paths;
    static std::unordered_map<std::string, std::wstring> texts;
    static std::unordered_map<std::string, sf::Texture> textures;
    static std::unordered_map<std::string, sf::SoundBuffer> soundEffects;
    static std::unordered_map<std::string, sf::Music> music;
};

#endif
