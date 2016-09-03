#ifndef WORLD_HPP

#define WORLD_HPP


#include "ResourceHolder.hpp"
#include "ResourceIdentifiers.hpp"
#include "SceneNode.hpp"
#include "Aircraft.hpp"


#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>



#include <array>


class World
	: private sf::NonCopyable
{
public:
												World(sf::RenderWindow & window);
	void										update(sf::Time deltaT);
	void										draw();

private:
	enum Layer 
	{ 
		Background, 
		Air,
		LayerCount 
	};


	struct WorldData
	{
		sf::FloatRect Bounds;
		float ScrollSpeed;
	};


	sf::RenderWindow &							mWindow;
	sf::View									mView;
	TextureHolder								mTextureHolder;
	FontHolder									mFontHolder;
	SceneNode									mSceneGraph;
	std::array<SceneNode *, LayerCount>			mSceneLayers;
	WorldData									mWorld;
	Aircraft *									mPlayer;
	sf::Vector2f								mSpawnPosition;

private:
	void										loadTextures();
	void										loadFonts();
	void										buildScene();
};


#endif // !WORLD_HPP
