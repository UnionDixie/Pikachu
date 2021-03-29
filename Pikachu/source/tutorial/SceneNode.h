#include <SFML/Graphics.hpp>
#include <memory>
#include <cassert>
#include <algorithm>

class SceneNode : public sf::Transformable,
				  public sf::Drawable,
				  private sf::NonCopyable
{ 
public:
	typedef std::unique_ptr<SceneNode> Ptr;
	SceneNode();
	void attachChild(Ptr);
	Ptr detachChild(const SceneNode&);
	~SceneNode();
private:
	virtual void draw(sf::RenderTarget&,
		              sf::RenderStates) const;
	virtual void drawCurrent(sf::RenderTarget&,
						  sf::RenderStates) const;
	void drawChildren(sf::RenderTarget&,
			       sf::RenderStates) const;

private:
	std::vector<Ptr> children;
	SceneNode* parent;
};

