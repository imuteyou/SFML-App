#include "Entity.hpp"

Entity::Entity()
{
}

void Entity::setVelocity(sf::Vector2f velocity)
{
	mVelocity = velocity;
}

void Entity::addVelocity(sf::Vector2f velocity)
{
	mVelocity += velocity;
}

void Entity::setVelocity(float vx, float vy)
{
	mVelocity.x = vx;
	mVelocity.y = vy;
}

void Entity::addVelocity(float vx, float vy)
{
	mVelocity.x += vx;
	mVelocity.y += vy;
}

sf::Vector2f Entity::getVelocity()
{
	return mVelocity;
}

void Entity::updateCurrent(sf::Time deltaT)
{
	move(mVelocity * deltaT.asSeconds());
}
