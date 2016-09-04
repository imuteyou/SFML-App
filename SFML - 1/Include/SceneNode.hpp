#ifndef SCENENODE_HPP

#define SCENENODE_HPP

#include "Category.hpp"


#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>


#include <memory>
#include <vector>


struct Command;

class SceneNode
	: public sf::Transformable
	, public sf::Drawable
	, private sf::NonCopyable
{
public:
	typedef std::unique_ptr<SceneNode>				Ptr;

public:
													SceneNode();
	void											attachChild(Ptr child);
	Ptr												detachChild(const SceneNode & node);
	void											update(sf::Time deltaT);

private:
	std::vector<Ptr>								mChildren;
	SceneNode*										mParent;

private:
	void											draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void									drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void									drawChildren(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void									updateCurrent(sf::Time deltaT);
	void											updateChildren(sf::Time deltaT);
	void											onCommand(const Command & command, sf::Time deltaT);
	sf::Transform									getWorldTransform() const;
	sf::Vector2f									getWorldPosition() const;
	virtual unsigned int							getCategory() const;
};



#endif // !SCENENODE_HPP
