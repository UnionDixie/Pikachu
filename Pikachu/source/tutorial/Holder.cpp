#include "Holder.h"

Holder::Holder()
{
	sf::Texture backT, m_playerT, enemyT, foodT, finalScoreT, menuT;
	backT.loadFromFile("data/background.png");
	m_playerT.loadFromFile("data/pikachu.png");
	enemyT.loadFromFile("data/enemy.png");
	foodT.loadFromFile("data/food.png");
	finalScoreT.loadFromFile("data/finalScore.png");
	menuT.loadFromFile("data/intro_2.png");

	m_textures["background"] = std::make_unique<sf::Texture>(backT);
	m_textures["pikachu"] = std::make_unique<sf::Texture>(m_playerT);
	m_textures["enemy"] = std::make_unique<sf::Texture>(enemyT);
	m_textures["food"] = std::make_unique<sf::Texture>(foodT);
	m_textures["finalScore"] = std::make_unique<sf::Texture>(finalScoreT);
	m_textures["intro_2"] = std::make_unique<sf::Texture>(menuT);

	m_player = sf::Sprite(*m_textures["pikachu"].get());
	m_background = sf::Sprite(*m_textures["background"].get());
	m_food = sf::Sprite(*m_textures["food"].get());
	m_enemy = sf::Sprite(*m_textures["enemy"].get());
	m_end = sf::Sprite(*m_textures["finalScore"].get());
	m_menu = sf::Sprite(*m_textures["intro_2"].get());

	m_player.setPosition(500, 530);
	m_food.setPosition(500, 10);
	m_enemy.setPosition(300, 10);

	m_sprites.push_back(&m_background);

	//

	m_font.loadFromFile("data/fonts/OpenSans-Bold.ttf");
	m_text.setFont(m_font);
	m_text.setFillColor(sf::Color::Red);
	m_text.setString("0_0");
	m_text.setPosition(200, 200);
	m_text.setCharacterSize(30);

	m_meow.loadFromFile("data/music/piKAchu cute.wav");
	m_gameover.loadFromFile("data/music/game over.wav");
	m_fonMusic.loadFromFile("data/music/cycling_cut.wav");

	m_s1.setBuffer(m_meow);
	m_s2.setBuffer(m_gameover);
	m_s3.setBuffer(m_fonMusic);
}
