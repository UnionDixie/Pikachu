#include "game.h"

#include <random>
#include <iostream>



int rnd() {
	std::random_device r;
	std::default_random_engine e1(r());
	int a = 50, b = 900;
	std::uniform_int_distribution<int> uniform_dist(a, b);
	return uniform_dist(e1);
}

Game::Game() : window(sf::VideoMode(960,720),"PIKACHU >_<")
{
	window.setFramerateLimit(60);

	sf::Texture backT, playerT, enemyT, foodT, finalScoreT, menuT;
	backT.loadFromFile("data/background.png");
	playerT.loadFromFile("data/pikachu.png");
	enemyT.loadFromFile("data/enemy.png");
	foodT.loadFromFile("data/food.png");
	finalScoreT.loadFromFile("data/finalScore.png");
	menuT.loadFromFile("data/intro_2.png");

	textures["background"] = std::make_unique<sf::Texture>(backT);
	textures["pikachu"] = std::make_unique<sf::Texture>(playerT);
	textures["enemy"] = std::make_unique<sf::Texture>(enemyT);
	textures["food"] = std::make_unique<sf::Texture>(foodT);
	textures["finalScore"] = std::make_unique<sf::Texture>(finalScoreT);
	textures["intro_2"] = std::make_unique<sf::Texture>(menuT);

	player = sf::Sprite(*textures["pikachu"].get());
	background = sf::Sprite(*textures["background"].get());
	food = sf::Sprite(*textures["food"].get());
	enemy = sf::Sprite(*textures["enemy"].get());
	end = sf::Sprite(*textures["finalScore"].get());
	menu = sf::Sprite(*textures["intro_2"].get());

	player.setPosition(500, 530);
	food.setPosition(500, 10);
	enemy.setPosition(300, 10);

	sprites.push_back(&background);
	

	const int y = 5;
	for (size_t i = 0; i < 5; i++)
	{
		auto x = rnd();
		entity.push_back(std::make_pair(food, 1));
		entity.rbegin()->first.setPosition(sf::Vector2f(x, y));
		x = rnd();
		entity.push_back(std::make_pair(enemy, 2));
		entity.rbegin()->first.setPosition(sf::Vector2f(x, y));
	}

	font.loadFromFile("data/fonts/OpenSans-Bold.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::Red);
	text.setString("Fuck off");
	text.setPosition(200, 200);
	text.setCharacterSize(30);

	meow.loadFromFile("data/music/piKAchu cute.wav");
	gameover.loadFromFile("data/music/game over.wav");
	fonMusic.loadFromFile("data/music/cycling_cut.wav");

	s1.setBuffer(meow);
	s2.setBuffer(gameover);
	s3.setBuffer(fonMusic);
	
	s3.setLoop(true);
	
}

void Game::run() {
	s3.play();
	while (isMenu)
	{
		window.clear(sf::Color::White);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
				isMenu = false;
			}
			if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					isMenu = false;
				}
			}
		}
		window.draw(menu);
		window.display();
	}
	while (window.isOpen())
	{
		if (live) {
			update();
			render();
		}
		else {	
			window.clear(sf::Color::White);
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();
				if (event.type == sf::Event::KeyPressed) {
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
						live = true;

						for (auto&& it : entity)
						{
							it.first.setPosition(sf::Vector2f(rnd(), -5));
						}

						hp = 100;
						score = 0;
						text.setPosition(200, 200);
						player.setPosition(500, 530);
						s3.play();
					}
				}
			}
			window.draw(end);
			window.draw(text);
			window.display();
		}
	}
}

void Game::update()
{
	const sf::Vector2f gravity = sf::Vector2f(0.f, 9.8f);

	sf::Vector2f move = sf::Vector2f(0.f, 0.f);
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		if (event.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !jump) {
				s1.play();
				move.y = -25.0f;
				jump = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				move.x = -1.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				move.x = 1.0f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F1)) {
				hp = 1000;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
				hp = 100;
			}

		}	
	}
	sf::Vector2f speed = sf::Vector2f(5.0f, 5.0f);
	move.x *= speed.x;
	move.y *= speed.y;

	player.move(move);

	if (player.getPosition().x < 1 || player.getPosition().x > 800) {
		player.setPosition(player.getPosition() - move);
	}
	if (player.getPosition().y < 530 && jump) {
		player.move(sf::Vector2f(0.0f, 1.0f));
	}
	if (player.getPosition().y >= 530) {
		jump = false;
	}

	
	float timeSpeed = 0.4f;


	for (auto it = entity.begin(); it != entity.end(); it++) {
		it->first.move(timeSpeed * gravity);

		if (it->first.getGlobalBounds().intersects(player.getGlobalBounds())) {
			if (it->second == 1) {
				if (hp < 100)
					hp++;
				score++;
			}
			else {
				hp -= 25;//quat of life
			}
			it->first.setPosition(sf::Vector2f(rnd(), 5));
			std::cout << hp << " " << score << "\n";

			if (hp <= 0) {
				live = false;
				s3.stop();
				s2.play();
				text.setString(std::to_string(score));
				text.setPosition(sf::Vector2f(505, 630));
				return;
			}

		}
		const int y = -5;
		if (it != entity.end() && it->first.getPosition().y > 720) {
			it->first.setPosition(sf::Vector2f(rnd(), 5));
		}
	}

	text.setString(std::string("HP: ") + std::to_string(hp));

}

void Game::render()
{
	window.clear(sf::Color::White);
	for (const auto& it : sprites) {
		window.draw(*it);
	}
	window.draw(text);
	for (const auto& it : entity) {
		window.draw(it.first);
	}
	window.draw(player);
	window.display();
	
}




Game::~Game()
{
}