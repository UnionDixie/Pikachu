#include <utility>
#include <SFML/Graphics.hpp>
#include <random>

class Food
{
public:
	Food();
	Food(sf::Texture,sf::IntRect);
	void set(sf::Texture, sf::IntRect);
	void update(int);//speed
	std::vector<sf::Sprite>* getFood();
	~Food();
private:
	void initRandom();
	int getRandom(int, int);
    std::random_device r;
	std::default_random_engine e1;
	sf::Texture texture;
	sf::IntRect rect;
	std::pair<int, int> pos, vel;
	std::vector<sf::Sprite> food;
};
