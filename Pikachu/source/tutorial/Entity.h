#include <SFML/Graphics.hpp>

#include "rnd.h"

//#include "../tutorial/SceneNode.h"

class Entity : public sf::Transformable,
	           public sf::Drawable,
	           private sf::NonCopyable
{
public:
	Entity(const sf::Texture& texture,int id = -1) noexcept;
	virtual void draw(sf::RenderTarget& target,
		sf::RenderStates states) const;

	void update(sf::Time dt);
	const sf::FloatRect& getBound() const;
	const int getID() const;

	~Entity();
private:
	int id;
	sf::Vector2f velocity;
	sf::Sprite frame;
};

