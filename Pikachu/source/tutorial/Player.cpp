#include "Player.h"

Player::Player() : m_vel(sf::Vector2f(0.f,0.f))
{
}

void Player::setTexture(const sf::Texture& texture)
{
	m_dataTexture = texture;
	m_drawSprite.setTexture(m_dataTexture);

	const sf::FloatRect bounds = m_drawSprite.getGlobalBounds();

	m_drawSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_drawSprite, states);
}

void Player::update(sf::Time dt, sf::Vector2f move)
{
	m_drawSprite.move(move * dt.asSeconds());
}

void Player::checkColl(const std::vector<Entity>& entity)
{
	const auto playerBox = m_drawSprite.getGlobalBounds();

	for (const auto& it : entity) {
		const auto boxIt = it.getBound();
		if (playerBox.intersects(boxIt)) {
			const auto itID = it.getID();
			if (itID == 1) {
				m_score += 15;
				m_hp++;
			}
			else if (itID == 2) {
				m_hp -= 10;
			}
		}
	}
}

void Player::addHp(int hp)
{
	m_hp += hp;
}

void Player::hit(int damage)
{
	m_hp -= damage;
}

int Player::currHp() const
{
	return m_hp;
}

void Player::addScore(int score)
{
	m_score += score;
}

int Player::score() const
{
	return m_score;
}

bool Player::isLive() const
{
	return m_hp > 0;
}

bool Player::isJump() const
{
	return m_jump;
}

void Player::jump()
{
	m_jump = true;
}



