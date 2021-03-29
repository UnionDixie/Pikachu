#include <SFML/Graphics.hpp>

#include "../tutorial/SceneNode.h"

class Entity : public SceneNode
{
public:
	Entity();
	void setVelocity(sf::Vector2f);
	sf::Vector2f getVelocity() const;
	~Entity();
private:
	virtual void updateCurrent(sf::Time dt);
	sf::Vector2f velocity;
};

