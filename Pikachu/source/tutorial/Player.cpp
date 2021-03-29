#include "Player.h"

Player::Player(Type type) : type(type)
{
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Player::~Player()
{
}

