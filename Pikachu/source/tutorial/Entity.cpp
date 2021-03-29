#include "Entity.h"

Entity::Entity()
{
}

void Entity::setVelocity(sf::Vector2f newvelocity)
{
	velocity = newvelocity;
}

sf::Vector2f Entity::getVelocity() const
{
	return velocity;
}

Entity::~Entity()
{
}

void Entity::updateCurrent(sf::Time dt)
{
	sf::Transformable::move(velocity * dt.asSeconds());
}
