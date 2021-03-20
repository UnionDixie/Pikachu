#include "player.h"


Player::Player()
{
	pos = { 0,0 };
	info = { 3,true };
	int foods = 0;

	events["food"] = [&]() { foods++; };
	events["enemy"] = [&]() { info.first--; info.second = info.first; };
	events["move"] = [&]() {};
}

Player::Player(sf::Texture texture, sf::IntRect rect) : Player()
{
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
}

Player::Player(sf::Sprite sp, sf::IntRect rect) : Player(*sp.getTexture(),rect)
{
}

void Player::set(sf::Texture t, sf::IntRect r)
{
	
	if (!buffer.loadFromFile("data/music/piKAchu cute.wav"))
		std::cout << "error\n";
	sound.setBuffer(buffer);
	texture = t;
	rect = r;
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	sprite.setPosition(sf::Vector2f(400, 530));
}

void Player::update(std::pair<int, int> move, std::string state) {

	if (state == "move") {
		pos = sprite.getPosition();
		pos.x += move.first;
		pos.y += move.second;
		sprite.setPosition(pos);
		{
			if (move.second != 0) {
				sound.play();
			}
		}

	}
	else {
		events[state]();
	}

}

sf::Sprite* Player::drawS()
{
	return &sprite;
}

const std::pair<sf::Sprite, std::pair<int, bool>>& Player::get() const
{
	return { sprite,info };
}

Player::~Player()
{

}