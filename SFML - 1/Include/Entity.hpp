#ifndef ENTITY_HPP

#define ENTITY_HPP


#include "SceneNode.hpp"



#include <SFML/System/Vector2.hpp>


class Entity
	: public SceneNode
{
public:
												Entity();

private:
	sf::Vector2f								mVelocity;

private:
	virtual void								setVelocity(sf::Vector2f velocity);
	virtual void								addVelocity(sf::Vector2f velocity);
	virtual void								setVelocity(float vx, float vy);
	virtual void								addVelocity(float vx, float vy);
};



#endif // !ENTITY_HPP
