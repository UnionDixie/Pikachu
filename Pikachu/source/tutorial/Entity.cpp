#include "Entity.h"


Entity::Entity(const sf::Texture& texture, int id) noexcept :
	m_frame(texture), m_velocity(sf::Vector2f(0, 1.0f)), m_id(id)
{
	constexpr int min = 10;
	constexpr int max = 100;

	const sf::Vector2f pos(sf::Vector2f(Random::rnd(min, max), -2));
	m_frame.setPosition(pos);

	const sf::FloatRect bounds = m_frame.getGlobalBounds();
	m_frame.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_frame, states);
}


void Entity::update(sf::Time dt)
{
	m_frame.move(dt.asSeconds() * m_velocity);
}

sf::FloatRect Entity::getBound() const {
	return m_frame.getGlobalBounds();
}

const int Entity::getID() const
{
	return m_id;
}

