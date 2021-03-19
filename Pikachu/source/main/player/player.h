#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	void update();
	sf::Sprite draw() const;
	~Player();
private:
	sf::Sprite sprite;
	std::pair<int, int> pos;
	std::pair<int, bool> info = { 3,true };

};
