#include <SFML/Graphics.hpp>

#include "rnd.h"

class Entity : public sf::Transformable,
	           public sf::Drawable,
	           private sf::NonCopyable
{
public:
	Entity() = default;
	Entity(const sf::Texture& texture, int id = -1) noexcept;
	~Entity() = default;
public:
	virtual void draw(
		sf::RenderTarget& target,
		sf::RenderStates states) const;
	void update(sf::Time dt);
public:
	sf::FloatRect getBound() const;
	const int getID() const;
private:
	int m_id;
	sf::Vector2f m_velocity;
	sf::Sprite m_frame;
};

