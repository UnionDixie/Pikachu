#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <list>
#include <map>
#include <memory>

#include <Box2D/Box2D.h>

class Game
{
public:
	Game();
	void run();
	~Game();	
private:
	void update();
	void render();
	void renderGame();
	void renderMenu();
	void renderEnd();
private:
	const float SCALE = 30.f;
	const float DEG = 57.29f;
	float32 x = 0.f, y = 9.8f;
	b2Vec2 grav = b2Vec2(x, y);
	b2World World = b2World(grav);
	b2Body* pBody;
private:
	sf::RenderWindow window;
	sf::Sprite background, player, food, enemy, end, menu, earth;
	std::map<std::string, std::unique_ptr<sf::Texture>> textures;
	std::list<sf::Sprite*> sprites;

	std::list<std::pair<sf::Sprite,int>> entity;

	int score = 0;
	int hp = 100;
	bool live = true;
	bool jump = false;
	bool isMenu = true;
	bool isRun = true;

	sf::Font font;
	sf::Text text;

	sf::SoundBuffer meow,gameover,fonMusic;
	sf::Sound s1, s2,s3;

};


