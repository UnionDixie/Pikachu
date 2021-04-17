#include <SFML/Graphics.hpp>
#include <memory>
#include <cassert>
#include <algorithm>

namespace Layer {
	enum Type {
		Background,
		Air,
		LayerCount
	};
}

class SceneNode : public sf::Transformable,
				  public sf::Drawable,
				  private sf::NonCopyable
{ 
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	SceneNode();
	void attachChild(Ptr);
	Ptr detachChild(const SceneNode&);
	void update(sf::Time);
	sf::Transform getWorldTransform() const;
	sf::Vector2f getWorldPosition() const;
	~SceneNode();
private:
	virtual void draw(sf::RenderTarget&,
		              sf::RenderStates) const;
	virtual void drawCurrent(sf::RenderTarget&,
						  sf::RenderStates) const;
	void drawChildren(sf::RenderTarget&,
			       sf::RenderStates) const;
	virtual void updateCurrent(sf::Time);
	void updateChildren(sf::Time);

private:
	std::vector<Ptr> children;
	SceneNode* parent;
};

