#include "game.h"

#include <random>
#include <iostream>

static int rnd() {
	std::random_device r;
	std::default_random_engine e1(r());
	constexpr int min = 50, max = 900;
	std::uniform_int_distribution<int> uniform_dist(min, max);
	return uniform_dist(e1);
}

Game::Game() : m_window(sf::VideoMode(960,720),"PIKACHU >_<")
{
	init();
}

void Game::init()
{
	m_window.setFramerateLimit(60);
	//set pos for food
	const int y = -5;
	const int nFood = 5;
	for (size_t i = 0; i < nFood; i++)
	{
		int x = rnd();
		holder.m_entity.push_back(std::make_pair(holder.m_food, 1));
		holder.m_entity.rbegin()->first.setPosition(sf::Vector2f(x, y));
		x = rnd();
		holder.m_entity.push_back(std::make_pair(holder.m_enemy, 2));
		holder.m_entity.rbegin()->first.setPosition(sf::Vector2f(x, y));
	}

	holder.m_s3.setLoop(true);
	holder.m_s3.setVolume(10.f);
}

void Game::run() 
{
	startMusicFon();
	renderMenu();
	renderGame();
}

void Game::input()
{
	m_move = {};

	sf::Event event;

	//use state machine and command pattern
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed ||
			sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			m_window.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !m_jump)
			playerJump();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			m_move.x = -1.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			m_move.x = 1.0f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			m_hp = 1000;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
			m_hp = 100;	
	}
}

//sheet
void Game::update()
{
	auto& m_player = holder.m_player;
	auto& m_entity = holder.m_entity;
	auto& m_s3 = holder.m_s3;
	auto& m_s2 = holder.m_s2;
	auto& m_text = holder.m_text;


	const sf::Vector2f gravity = sf::Vector2f(0.f, 9.8f);
	
	sf::Vector2f speed = sf::Vector2f(5.0f, 5.0f);
	m_move.x *= speed.x;
	m_move.y *= speed.y;

	m_player.move(m_move);

	if (m_player.getPosition().x < 1 || m_player.getPosition().x > 800) {
		m_player.setPosition(m_player.getPosition() - m_move);
	}
	if (m_player.getPosition().y < 530 && m_jump) {
		m_player.move(sf::Vector2f(0.0f, 1.0f));
	}
	if (m_player.getPosition().y >= 530) {
		m_jump = false;
	}

	float timeSpeed = 0.4f;

	for (auto it = m_entity.begin(); it != m_entity.end(); it++) {
		it->first.move(timeSpeed * gravity);

		if (it->first.getGlobalBounds().intersects(m_player.getGlobalBounds())) {
			if (it->second == 1) {
				if (m_hp < 100)
					m_hp++;
				m_score++;
			}
			else {
				m_hp -= 25;//quat of life
			}
			it->first.setPosition(sf::Vector2f(rnd(), 5));
			std::cout << m_hp << " " << m_score << "\n";

			if (m_hp <= 0) {
				m_live = false;
				m_s3.stop();
				m_s2.play();
				m_text.setString(std::to_string(m_score));
				m_text.setPosition(sf::Vector2f(505, 630));
				return;
			}

		}
		const int y = -5;
		if (it != m_entity.end() && it->first.getPosition().y > 720) {
			it->first.setPosition(sf::Vector2f(rnd(), 5));
		}
	}

	m_text.setString(std::string("HP: ") + std::to_string(m_hp));

}

void Game::render()
{
	m_window.clear(sf::Color::White);
	//
	for (const auto& it : holder.m_sprites)
		m_window.draw(*it);
	//
	m_window.draw(holder.m_text);
	//
	for (const auto& it : holder.m_entity)
		m_window.draw(it.first);
	//
	m_window.draw(holder.m_player);
	//
	m_window.display();
	
}

void Game::renderGame()
{
	while (m_window.isOpen() && m_isRun)
	{
		if (m_live) {
			input();
			update();
			render();
		}
		else {
			renderEnd();
		}
	}
}

void Game::renderMenu()
{
	while (m_isMenu && m_isRun)
	{
		m_window.clear(sf::Color::White);
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			checkClose(event);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				startGame();
		}
		m_window.draw(holder.m_menu);
		m_window.display();
	}
}

void Game::renderEnd()
{
	m_window.clear(sf::Color::White);

	sf::Event event;
	while (m_window.pollEvent(event))
	{
		checkClose(event);
		checkNewGame(event);
	}

	m_window.draw(holder.m_end);
	m_window.draw(holder.m_text);

	m_window.display();
}

void Game::playerJump()
{
	holder.m_s1.play();
	m_move.y = -25.0f;
	m_jump = true;
}

void Game::closeGame()
{
	m_window.close();
	m_isMenu = false;
	m_isRun = false;
}

void Game::startGame()
{
	m_isMenu = false;
}

void Game::restartGame()
{
	m_live = true;
	for (auto&& it : holder.m_entity)
	{
		it.first.setPosition(sf::Vector2f(rnd(), -5));
	}
	m_hp = 100;
	m_score = 0;
	holder.m_text.setPosition(200, 200);
	holder.m_player.setPosition(500, 530);
	holder.m_s3.play();
}

void Game::clearScreen()
{
	m_window.clear(sf::Color::White);
}

void Game::startMusicFon()
{
	holder.m_s3.play();
}

void Game::checkClose(sf::Event& ev)
{
	if (ev.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		closeGame();
}

void Game::checkNewGame(sf::Event& ev)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		restartGame();
}
