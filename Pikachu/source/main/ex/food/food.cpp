#include "food.h"

Food::Food()
{
	initRandom();
}

Food::Food(sf::Texture t, sf::IntRect r) : texture(t),rect(r)
{

}

void Food::set(sf::Texture t , sf::IntRect r)
{	
	texture = t;
	rect = r;
	const int n = 10;
	for (size_t i = 0; i < n; i++)
	{
		food.emplace_back(texture, rect);
		food.back().setPosition(sf::Vector2f(getRandom(30, 920), getRandom(-100, -5)));
	}
}

void Food::update(int speed)
{
	for (auto it = food.begin();it!=food.end();++it)
	{
		auto& pos = it->getPosition();
		if (pos.y + speed * 2 > 950) {
			it->setPosition(sf::Vector2f(getRandom(30, 920), getRandom(-100, -5)));
		}
		else {
			it->setPosition(pos.x, pos.y + speed * 2 * 0.09);
		}
	}
}

std::vector<sf::Sprite>* Food::getFood()
{
	return &food;
}

Food::~Food()
{
}

void Food::initRandom()
{
	std::default_random_engine e2(r());
	e1 = e2;
}

int Food::getRandom(int min, int max)//10 950
{
	std::uniform_int_distribution<int> uniform_dist(min, max);
	return uniform_dist(e1);
}
