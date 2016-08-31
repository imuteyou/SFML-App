#ifndef SCENENODE_HPP

#define SCENENODE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/NonCopyable.hpp>


#include <memory>
#include <vector>



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

private:
	std::vector<Ptr>								mChildren;
	SceneNode*										mParent;

private:
	virtual void									draw(sf::RenderTarget & target, sf::RenderStates states) const;
	virtual void									drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
};



#endif // !SCENENODE_HPP
