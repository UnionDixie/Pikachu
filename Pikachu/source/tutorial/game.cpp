#include "game.h"

Game::Game() : window(sf::VideoMode(960,720),"Game")//, player()
{
	//window.setFramerateLimit(60);
	//window.setVerticalSyncEnabled(true);
	int cnt = 0;
	for (auto&& name : names) {
		tHolder.load(name,"data/"+name+".png");
		if (auto&& found = tHolder.get(name); found != std::nullopt) {
			sprites.try_emplace(name,*found);
		}
	}
	sprites["pikachu"].setPosition(sf::Vector2f(400, 530));
}

void Game::run() {
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	
	while (window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processEvents();
			update(TimePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{		
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handleInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handleInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			window.close();
			break;
		default:
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	sf::Vector2f move(0.f, 0.f);
	/*for (const auto& it : keyboards) {
		if (it.second) {
			move
		}
	}*/
	if (IsMovingUp)
		move.y -= playerSpeed;
	if (IsMovingDown)
		move.y += playerSpeed;
	if (IsMovingLeft)
		move.x -= playerSpeed;
	if (IsMovingRight)
		move.x += playerSpeed;
	sprites["pikachu"].move(move * deltaTime.asSeconds());
}

void Game::render()
{
	window.clear(sf::Color::White);
	for (auto&& it : sprites) {
		window.draw(it.second);
	}
	window.display();
}

void Game::handleInput(sf::Keyboard::Key key, bool isPressed)
{
	//keyboards[key] = isPressed;
	if (key == sf::Keyboard::W)
		IsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		IsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		IsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		IsMovingRight = isPressed;	else if (key == sf::Keyboard::Escape)
		window.close();

}


Game::~Game()
{
}