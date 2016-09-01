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
