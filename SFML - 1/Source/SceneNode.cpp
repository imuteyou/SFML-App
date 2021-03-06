#include "SceneNode.hpp"
#include "Command.hpp"


#include <utility>
#include <algorithm>
#include <cassert>



SceneNode::SceneNode()
	: mChildren()
	, mParent(nullptr)
{
}

void SceneNode::attachChild(Ptr child)
{
	child->mParent = this;
	mChildren.push_back(std::move(child));
}


SceneNode::Ptr SceneNode::detachChild(const SceneNode & node)
{
	auto found = std::find_if(mChildren.begin(), mChildren.end(), [&](Ptr & p) -> bool { return p.get() == &node; });

	assert(found != mChildren.end());

	Ptr result = std::move(*found);
	result->mParent = nullptr;
	mChildren.erase(found);
	return result;
}

void SceneNode::update(sf::Time deltaT)
{
	updateCurrent(deltaT);
	updateChildren(deltaT);
}

void SceneNode::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	drawCurrent(target, states);
	drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	
}

void SceneNode::drawChildren(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const Ptr & child : mChildren)
		child->draw(target, states);
}

void SceneNode::updateCurrent(sf::Time deltaT)
{
}

void SceneNode::updateChildren(sf::Time deltaT)
{
	for (Ptr & child : mChildren)
		child->update(deltaT);
}

void SceneNode::onCommand(const Command & command, sf::Time deltaT)
{
	if (command.category & getCategory())
		command.action(*this, deltaT);

	for (Ptr & child : mChildren)
		child->onCommand(command, deltaT);
}

sf::Transform SceneNode::getWorldTransform() const
{
	sf::Transform transform;

	for (const SceneNode * node = this; node != nullptr; node = node->mParent)
		transform *= node->getTransform();

	return transform;
}

sf::Vector2f SceneNode::getWorldPosition() const
{
	return getWorldTransform() * sf::Vector2f();
}

unsigned int SceneNode::getCategory() const
{
	return Category::Scene;
}
