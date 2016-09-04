#include "Aircraft.hpp"
#include "Command.hpp"

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
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
}

void Aircraft::drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(mSprite, states);
}

unsigned int Aircraft::getCategory() const
{
	switch (mType)
	{
		case Eagle:
			return Category::PlayerAircraft;

		case Raptor:
			return Category::AlliedAircraft;

		default:
			return Category::EnemyAircraft;
	}
}
