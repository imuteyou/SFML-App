#ifndef RESOURCEIDENTIFIERS_HPP

#define RESOURCEIDENTIFIERS_HPP


#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>


namespace sf
{
	class Texture;
	class Font;
}

namespace Textures
{
	enum ID { Landscape, Eagle, Raptor, Missile };
}

namespace Fonts
{
	enum ID { Statistics };
}


template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;

#endif