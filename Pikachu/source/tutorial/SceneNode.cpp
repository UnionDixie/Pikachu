#include "SceneNode.h"

typedef std::unique_ptr<SceneNode> Ptr;

SceneNode::SceneNode() : children(),parent(nullptr)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->parent = this;
	children.push_back(std::move(child));
}

Ptr SceneNode::detachChild(const SceneNode& node)
{
	auto found = 
	std::find_if(children.begin(), children.end(),
	[&](Ptr& p) {
			return p.get() == &node;
	});	
	assert(found != children.end() && "Not found child");
	
	Ptr result = std::move(*found);
	result->parent = nullptr;
	children.erase(found);
	return result;
}



void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	//default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const auto& it : children) {
		it->draw(target, states);
	}
}



SceneNode::~SceneNode()
{
}