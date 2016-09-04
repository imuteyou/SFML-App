#ifndef AIRCRAFT_HPP

#define AIRCRAFT_HPP

#include "Entity.hpp"
#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"

#include <SFML\Graphics\RenderStates.hpp>
#include <SFML\Graphics\RenderTarget.hpp>
#include <SFML\Graphics\Sprite.hpp>

class Aircraft
	: public Entity
{

public:
	enum									Type { Eagle, Raptor };

public:
											Aircraft(Type type, const TextureHolder & textures);

	virtual void							drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
	Textures::ID							toTextureID(Aircraft::Type type);


private:
	Type									mType;
	sf::Sprite								mSprite;

private:
	unsigned int							getCategory() const;

};

#endif // !AIRCRAFT_HPP
