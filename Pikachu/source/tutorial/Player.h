#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "Entity.h"

class Player : public sf::Transformable,
			   public sf::Drawable,
	           private sf::NonCopyable
{
public:
	Player();
	void setTexture(const sf::Texture& texture);
	virtual void draw(sf::RenderTarget& target,
					  sf::RenderStates states) const;
	void update(sf::Time dt, sf::Vector2f move);
	void checkColl(const std::list<Entity>& entity);
	~Player();
public://!!!!
	sf::Sprite drawSprite;
private:
	sf::Texture dataTexture;
	sf::Vector2f velocity;
private:
	int hp = 100;
	int score = 0;
	sf::Vector2f vel;
};

