#pragma once

#include <SFML/Graphics.hpp>

#include "../tutorial/Holder.h"

class Game
{
public:
	Game();
	void run();
	~Game() = default;	
private:
	void init();
	void update();
	void input();
	void render();
	void renderGame();
	void renderMenu();
	void renderEnd();
public:
	void playerJump();
	void closeGame();
	void startGame();
	void restartGame();
	void clearScreen();
	void startMusicFon();
	void checkClose(sf::Event& ev);
	void checkNewGame(sf::Event& ev);
private:
	sf::RenderWindow m_window;
	Holder holder;
private:
	int m_score = 0;
	int m_hp = 100;
	bool m_live = true;
	bool m_jump = false;
	bool m_isMenu = true;
	bool m_isRun = true;
	sf::Vector2f m_move;
};


