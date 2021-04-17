#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <cassert>

#include "ResourceHolder.hpp"
#include "Player.h"

class Game
{
public:
	Game();
	void run();
	~Game();
private:
	typedef ResourceHolder<sf::Texture, std::string> TextureHolder;
	TextureHolder tHolder;

	//Player player;
	sf::View view,player1,player2,minimap;

	void processEvents();
	void update(sf::Time);
	void render();
	void handleInput(sf::Keyboard::Key,bool);
	
	sf::RenderWindow window;

	//std::map < sf::Keyboard::Key , bool > keyboards;

	bool IsMovingUp = false,//w
		 IsMovingDown = false,//s
		 IsMovingLeft = false,//a
		 IsMovingRight = false;//d
	const float playerSpeed = 100.f;
	const sf::Time TimePerFrame 
		  = sf::seconds(1.f / 60.f);
	
	const std::vector<std::string> names
		  = { "background","pikachu" };	
	std::map<std::string, sf::Sprite> sprites;
};

