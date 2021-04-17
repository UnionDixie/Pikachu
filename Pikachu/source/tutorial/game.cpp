#include "game.h"

Game::Game() : window(sf::VideoMode(960,720),"Game"), 
			   view(sf::Vector2f(0.f, 0.f), sf::Vector2f(960.f, 720.f))
			   //player1(sf::Vector2f(480.f, 360.f), sf::Vector2f(960.f, 720.f)),
			   //player2(sf::Vector2f(480.f, 360.f), sf::Vector2f(960.f, 720.f))
			//, player(0, tHolder)
{
	//view.setViewport(sf::FloatRect(0.25f, 0.25, 0.5f, 0.5f));
	//window.setFramerateLimit(60);
	//window.setVerticalSyncEnabled(true);
	int cnt = 0;
	for (auto&& name : names) {
		tHolder.load(name,"data/"+name+".png");
		if (auto&& found = tHolder.get(name); found != std::nullopt) {
			auto it = sprites.try_emplace(name,*found);
			if (it.second) {
				auto size = found->get().getSize();
				sprites[name].setOrigin(size.x / 2, size.y / 2);
			}
		}
	}
	sprites["pikachu"].setPosition(sf::Vector2f(230, 250));

	// player 1 (left side of the screen)
	//player1.setViewport(sf::FloatRect(0.f, 0.f, 0.5f, 1.f));
	// player 2 (right side of the screen)
	//player2.setViewport(sf::FloatRect(0.5f, 0.f, 0.5f, 1.f));

	
	//view.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));//full game
	//minimap.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));

	view.setCenter(sprites["pikachu"].getPosition());


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
	sf::Vector2f moveView;
	if (IsMovingUp) {
		move.y -= playerSpeed;
		moveView.y -= playerSpeed;
	}
	if (IsMovingDown) {
		move.y += playerSpeed;
		moveView.y += playerSpeed;
	}
	if (IsMovingLeft) {
		move.x -= playerSpeed;
		moveView.x -= playerSpeed;
	}
	if (IsMovingRight) {
		move.x += playerSpeed;
		moveView.x += playerSpeed;
	}
	sprites["pikachu"].move(move * deltaTime.asSeconds());
	view.move(moveView * deltaTime.asSeconds());
}

void Game::render()
{
	window.setView(view);
	window.clear(sf::Color::White);
	for (auto&& it : sprites) {
		window.draw(it.second);
	}
	/*window.setView(minimap);
	for (auto&& it : sprites) {
		window.draw(it.second);
	}*/

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
		IsMovingRight = isPressed;
	else if (key == sf::Keyboard::Escape)
		window.close();

}


Game::~Game()
{
}