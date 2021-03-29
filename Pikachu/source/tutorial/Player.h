#pragma once

#include "Entity.h"

#include "ResourceHolder.hpp"

class Player : public Entity
{
public:
	typedef ResourceHolder<sf::Texture, std::string> TextureHolder;
	TextureHolder tHolder;
	enum class Type
	{
		Live,
		Death,
	};
	explicit Player(Type type);
	virtual void drawCurrent(sf::RenderTarget& target,
							 sf::RenderStates states) const;
	~Player();
private:
	Type type;
	sf::Sprite sprite;
};

