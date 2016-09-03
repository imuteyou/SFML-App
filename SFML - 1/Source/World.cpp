#include "World.hpp"
#include "SpriteNode.hpp"

World::World(sf::RenderWindow & window)
	: mWindow(window)
	, mView(window.getDefaultView())
	, mWorld()
	, mSceneGraph()
	, mSceneLayers()
	, mPlayer(nullptr)
	, mSpawnPosition()
{
	mWorld.Bounds.left = 0.0f;
	mWorld.Bounds.top = 0.0f;
	mWorld.Bounds.height = 2000.0f;
	mWorld.Bounds.width = mView.getSize().x;
	mWorld.ScrollSpeed = -50.0f;

	mSpawnPosition.x = mView.getSize().x / 2.0f;
	mSpawnPosition.y = mWorld.Bounds.height - mView.getSize().y / 2.0f;

	loadTextures();
	loadFonts();
	buildScene();

	mView.setCenter(mSpawnPosition);
}

void World::update(sf::Time deltaT)
{
	mView.move(0.0f * deltaT.asSeconds(), mWorld.ScrollSpeed * deltaT.asSeconds());
	sf::Vector2f playerPosition = mPlayer->getPosition();
	sf::Vector2f playerVelocity = mPlayer->getVelocity();

	if (playerPosition.x <= mWorld.Bounds.left + 50.0f
		|| playerPosition.x >= mWorld.Bounds.left + mWorld.Bounds.width - 50.0f)
	{
		playerVelocity.x = -playerVelocity.x;
		mPlayer->setVelocity(playerVelocity);
	}

	mSceneGraph.update(deltaT);
}

void World::draw()
{
	mWindow.setView(mView);
	mWindow.draw(mSceneGraph);
}

void World::loadTextures()
{
	mTextureHolder.loadResource(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextureHolder.loadResource(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextureHolder.loadResource(Textures::Desert, "Media/Textures/Desert.png");
}

void World::loadFonts()
{
	mFontHolder.loadResource(Fonts::Statistics, "Media/Fonts/OpenSans-Bold.ttf");
}

void World::buildScene()
{
	for (short i = 0; i < LayerCount; i++)
	{
		SceneNode::Ptr layer(new SceneNode());
		mSceneLayers[i] = layer.get();
		mSceneGraph.attachChild(std::move(layer));
	}

	sf::Texture & texture = mTextureHolder.getResource(Textures::Desert);
	sf::IntRect textureRect(mWorld.Bounds);
	texture.setRepeated(true);

	std::unique_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
	backgroundSprite->setPosition(mWorld.Bounds.left, mWorld.Bounds.top);
	mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

	std::unique_ptr<Aircraft> leader(new Aircraft(Aircraft::Eagle, mTextureHolder));
	mPlayer = leader.get();
	mPlayer->setPosition(mSpawnPosition);
	mPlayer->setVelocity(40.0f, mWorld.ScrollSpeed);
	mSceneLayers[Air]->attachChild(std::move(leader));

	std::unique_ptr<Aircraft> leftEscort(new Aircraft(Aircraft::Eagle, mTextureHolder));
	leftEscort->setPosition(-80.0f, 50.0f);
	mPlayer->attachChild(std::move(leftEscort));

	std::unique_ptr<Aircraft> rightEscort(new Aircraft(Aircraft::Eagle, mTextureHolder));
	rightEscort->setPosition(80.0f, 50.0f);
	mPlayer->attachChild(std::move(rightEscort));
}
