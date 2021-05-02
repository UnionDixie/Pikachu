#include "Player.h"

Player::Player() : vel(sf::Vector2f(0.f,0.f))
{
	
}



void Player::setTexture(const sf::Texture& texture)
{
	dataTexture = texture;
	drawSprite.setTexture(dataTexture);
	sf::FloatRect bounds = drawSprite.getGlobalBounds();
	drawSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(drawSprite, states);
}

void Player::update(sf::Time dt, sf::Vector2f move)
{
	drawSprite.move(move * dt.asSeconds());
}

void Player::checkColl(const std::list<Entity>& entity)
{
	auto playerBox = drawSprite.getGlobalBounds();
	for (const auto& it : entity) {
		auto boxIt = it.getBound();
		if (playerBox.intersects(boxIt)) {
			auto itID = it.getID();
			if (itID == 1) {
				score += 5;
				hp += 1;
			}
			else if (itID == 2) {
				hp -= 25;
			}
		}
	}
}

Player::~Player()
{
}

