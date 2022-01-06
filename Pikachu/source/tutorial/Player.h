#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#pragma warning(push)
#pragma warning(disable:4244)
#include "Entity.h"
#pragma warning(pop)


class Player : public sf::Transformable,
			   public sf::Drawable,
	           private sf::NonCopyable
{
public:
	Player();
	~Player() = default;
public:
	void setTexture(const sf::Texture& texture);
	virtual void draw(
		sf::RenderTarget& target,
		sf::RenderStates states) const;
	void update(sf::Time dt, sf::Vector2f move);
public:
	void checkColl(const std::vector<Entity>& entity);
	void addHp(int hp);
	void hit(int damage);
	int currHp() const;
	void addScore(int score);
	int score() const;
	bool isLive() const;
	bool isJump() const;
	void jump();
public://!!!!
	sf::Sprite m_drawSprite;	
private:
	sf::Texture m_dataTexture;
	sf::Vector2f m_velocity;
	int m_hp = 100;
	int m_score = 0;
	bool m_jump = false;
	sf::Vector2f m_vel;
};

