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

	sf::Texture backT, playerT, enemyT, foodT, finalScoreT, menuT, ground;
	backT.loadFromFile("data/background.png");
	playerT.loadFromFile("data/pikachu.png");
	enemyT.loadFromFile("data/enemy.png");
	foodT.loadFromFile("data/food.png");
	finalScoreT.loadFromFile("data/finalScore.png");
	menuT.loadFromFile("data/intro_2.png");
	//
	ground.loadFromFile("data/ground.png");

	textures["background"] = std::make_unique<sf::Texture>(backT);
	textures["pikachu"] = std::make_unique<sf::Texture>(playerT);
	textures["enemy"] = std::make_unique<sf::Texture>(enemyT);
	textures["food"] = std::make_unique<sf::Texture>(foodT);
	textures["finalScore"] = std::make_unique<sf::Texture>(finalScoreT);
	textures["intro_2"] = std::make_unique<sf::Texture>(menuT);
	//
	textures["ground"] = std::make_unique<sf::Texture>(ground);

	player = sf::Sprite(*textures["pikachu"].get());
	background = sf::Sprite(*textures["background"].get());
	food = sf::Sprite(*textures["food"].get());
	enemy = sf::Sprite(*textures["enemy"].get());
	end = sf::Sprite(*textures["finalScore"].get());
	menu = sf::Sprite(*textures["intro_2"].get());
	//
	earth = sf::Sprite(*textures["ground"].get());

	player.setPosition(500, 430);
	food.setPosition(500, 10);
	enemy.setPosition(300, 10);
	//
	earth.setPosition(0, 580);

	sprites.push_back(&background);
	//
	//sprites.push_back(&earth);


	auto setWall = [&](int x, int y, int w, int h) {
		b2PolygonShape gr;
		gr.SetAsBox(w / SCALE, h / SCALE);

		b2BodyDef bdef;
		bdef.position.Set(x / SCALE, y / SCALE);

		b2Body* b_ground = World.CreateBody(&bdef);
		b_ground->CreateFixture(&gr, 1);
	};
	setWall(445, 600, 700, 50);
	setWall(-18, 0, 1, 700);
	setWall(840, 0, 1, 1000);
	setWall(0, 0, 2000, 1);
	//setWall(445, 600, 700, 40);
	


	b2BodyDef bdef;
	bdef.type = b2_dynamicBody;

	///////////////////////
	bdef.position.Set(2, 2);
	b2CircleShape circle;
	circle.m_radius = 16 / SCALE;
	pBody = World.CreateBody(&bdef);
	pBody->CreateFixture(&circle, 2);
	pBody->SetUserData((void*)"player");



	const int y = -5;
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
	text.setString("0_0");
	text.setPosition(200, 200);
	text.setCharacterSize(30);

	meow.loadFromFile("data/music/piKAchu cute.wav");
	gameover.loadFromFile("data/music/game over.wav");
	fonMusic.loadFromFile("data/music/cycling_cut.wav");

	s1.setBuffer(meow);
	s2.setBuffer(gameover);
	s3.setBuffer(fonMusic);
	
	s3.setLoop(true);
	s3.setVolume(10.f);
	
}

void Game::run() {
	s3.play();
	renderMenu();
	renderGame();	
}

void Game::update()
{
	World.Step(1 / 60.f, 8, 3);

	/////check if onGround//////
	bool onGround = 0;
	b2Vec2 pos = pBody->GetPosition();
	pos.y += 17 / SCALE;
	for (b2Body* it = World.GetBodyList(); it != 0; it = it->GetNext())
		for (b2Fixture* f = it->GetFixtureList(); f != 0; f = f->GetNext())
			if (f->TestPoint(pos))  onGround = true;
	/////////////////////////////


	const sf::Vector2f gravity = sf::Vector2f(0.f, 9.8f);

	sf::Vector2f move = sf::Vector2f(0.f, 0.f);
	sf::Event event;
	while (window.pollEvent(event))
	{

		b2Vec2 vel = pBody->GetLinearVelocity();
		float  angVel = pBody->GetAngularVelocity();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) if (vel.x < 20) { pBody->ApplyForceToCenter(b2Vec2(40, 0),0); if (angVel < 15) pBody->ApplyTorque(10,0); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  if (vel.x > -20) { pBody->ApplyForceToCenter(b2Vec2(-40, 0),0); if (angVel > -15)  pBody->ApplyTorque(-10,0); }
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    if (onGround)  pBody->ApplyForceToCenter(b2Vec2(0, -1200),0);


		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		if (event.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !jump) {
				s1.play();
				//move.y = -25.0f;
				//jump = true;
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


	for (b2Body* it = World.GetBodyList(); it != 0; it = it->GetNext())
	{
		b2Vec2 pos = it->GetPosition();
		float angle = it->GetAngle();

		if (it->GetUserData() == "player")
		{
			player.setPosition(pos.x * SCALE, pos.y * SCALE);
			//player.setRotation(angle * DEG);
			//window.draw(sPlayer);
		}
	}



	sf::Vector2f speed = sf::Vector2f(5.0f, 5.0f);
	move.x *= speed.x;
	//move.y *= speed.y;

	player.move(move);

	if (player.getPosition().x < 1 || player.getPosition().x > 800) {
		player.setPosition(player.getPosition() - move);
	}
	if (player.getPosition().y < 530 && jump) {
		//player.move(sf::Vector2f(0.0f, 1.0f));
	}
	if (player.getPosition().y >= 530) {
		//jump = false;
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

void Game::renderGame()
{
	while (window.isOpen() && isRun)
	{
		if (live) {
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
	while (isMenu && isRun)
	{
		window.clear(sf::Color::White);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
				isMenu = false;
				isRun = false;
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
}

void Game::renderEnd()
{
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




Game::~Game()
{
}