#include <utility>
#include <SFML/Graphics.hpp>
#include <random>

class Food
{
public:
	Food();
	void update();//random
	std::vector<sf::Sprite>& getFood() const;
	~Food();
private:
	std::pair<int, int> pos, vel;
	std::vector<sf::Sprite> food;
};
