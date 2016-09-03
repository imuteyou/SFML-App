#ifndef ENTITY_HPP

#define ENTITY_HPP


#include "SceneNode.hpp"



#include <SFML/System/Vector2.hpp>


class Entity
	: public SceneNode
{
public:
												Entity();

public:
	void										setVelocity(sf::Vector2f velocity);
	void										addVelocity(sf::Vector2f velocity);
	void										setVelocity(float vx, float vy);
	void										addVelocity(float vx, float vy);
	sf::Vector2f								getVelocity();
	virtual void								updateCurrent(sf::Time deltaT);

private:
	sf::Vector2f								mVelocity;


};



#endif // !ENTITY_HPP
