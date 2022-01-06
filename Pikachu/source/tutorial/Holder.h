#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <list>
#include <map>
#include <memory>

class Holder
{
public:
	Holder();
	~Holder() = default;
public:
	sf::Sprite m_background, m_player, m_food, m_enemy, m_end, m_menu;
	std::map<std::string, std::unique_ptr<sf::Texture>> m_textures;
	std::vector<sf::Sprite*> m_sprites;
	std::vector<std::pair<sf::Sprite, int>> m_entity;
public:
	sf::Font m_font;
	sf::Text m_text;
public:
	sf::SoundBuffer m_meow, m_gameover, m_fonMusic;
	sf::Sound m_s1, m_s2, m_s3;
};

