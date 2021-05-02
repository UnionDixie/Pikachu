#include "Entity.h"



Entity::Entity(const sf::Texture& texture, int id) noexcept : frame(texture), velocity(sf::Vector2f(0, 1.0f)), id(id)
{
	sf::Vector2f pos(sf::Vector2f(Random::rnd(10, 100), -2));
	frame.setPosition(pos);
	sf::FloatRect bounds = frame.getGlobalBounds();
	frame.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(frame, states);
}


void Entity::update(sf::Time dt)
{
	frame.move(dt.asSeconds() * velocity);
}

const sf::FloatRect& Entity::getBound() const {
	return frame.getGlobalBounds();
}

const int Entity::getID() const
{
	return id;
}


Entity::~Entity()
{
}
