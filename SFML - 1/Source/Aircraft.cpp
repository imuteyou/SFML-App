#include "Aircraft.hpp"

Textures::ID Aircraft::toTextureID(Aircraft::Type type)
{
	switch (type)
	{
	case Aircraft::Eagle:
		return Textures::Eagle;
	
	case Aircraft::Raptor:
		return Textures::Raptor;
	}
}


Aircraft::Aircraft(Type type, const TextureHolder& textures)
	: mType(type)
	, mSprite(textures.getResource(toTextureID(type)))
{
}

void Aircraft::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}
