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
	mWorld.Bounds.height = 20000.0f;
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
	mPlayer->setVelocity(0.0f, 0.0f);

	while (!mCommandQueue.isEmpty())
		mSceneGraph.onCommand(mCommandQueue.pop(), deltaT);


	sf::Vector2f velocity = mPlayer->getVelocity();
	if (velocity.x != 0.0f && velocity.y != 0.0f)
		mPlayer->setVelocity(velocity / sqrt(2.0f));

	mPlayer->addVelocity(0.0f, mWorld.ScrollSpeed);

	mSceneGraph.update(deltaT);

	sf::FloatRect viewBounds(mView.getCenter() - mView.getSize() / 2.0f, mView.getSize());
	const float borderDistance = 100.0f;
	sf::Vector2f position = mPlayer->getPosition();
	position.x = std::max(position.x, viewBounds.left + borderDistance);
	position.x = std::min(position.x, viewBounds.left + viewBounds.width - borderDistance);
	position.y = std::max(position.y, viewBounds.top + borderDistance);
	position.y = std::min(position.y, viewBounds.top + viewBounds.height - borderDistance);
	mPlayer->setPosition(position);

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
	texture.setSmooth(true);

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

CommandQueue & World::getCommandQueue()
{
	return mCommandQueue;
}
