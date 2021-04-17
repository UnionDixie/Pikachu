#include "Player.h"

Player::Player(Type type, const TextureHolder& textures) : type(type),
               sprite(textures.get("player")->get())
{
	sf::FloatRect bounds = sprite.getGlobalBounds();
	sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Player::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}

Player::~Player()
{
}

