#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>



#include "Game.hpp"
#include "StringHelpers.hpp"

const sf::Time Game::timePerFrame = sf::seconds(1.0f / 600.0f);

Game::Game()
	: mWindow(sf::VideoMode(800, 600), "SFML-APP")
	, mTextureHolder()
	, mFontHolder()
	, mStatistics()
{
}

void Game::run()
{
	loadResources();

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		handleRealTimeInput();
		handleEvents();
		timeSinceLastUpdate += clock.restart();

		while (timeSinceLastUpdate > timePerFrame)
		{
			handleRealTimeInput();
			handleEvents();
			update(timePerFrame);

			timeSinceLastUpdate -= timePerFrame;
		}
		render();
	}

}

void Game::render()
{
	mWindow.clear();

	//RENDER THE STATISTICS INFO IF F3 WAS PRESSED
	if(mStatistics.isActive)
		mWindow.draw(mStatistics.Text);

	mWindow.display();
}

void Game::update(sf::Time deltaT)
{
	updateStatistics(deltaT);
}

void Game::updateStatistics(sf::Time deltaT)
{
	mStatistics.NumberOfFrames += 1;
	mStatistics.UpdateTime += deltaT;

	if (mStatistics.UpdateTime >= sf::seconds(1.0f))
	{
		mStatistics.Text.setString(
			"FPS : " + toString(mStatistics.NumberOfFrames) + "\n" +
			"Sec/Upd : " + toString(mStatistics.UpdateTime.asSeconds() / mStatistics.NumberOfFrames));
		mStatistics.UpdateTime -= sf::seconds(1.0f);
		mStatistics.NumberOfFrames = 0;
	}
}

void Game::processInput()
{
	handleRealTimeInput();
	handleEvents();
}

void Game::handleRealTimeInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		mWindow.close();		
}

void Game::handleEvents()
{
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::F3)
				mStatistics.isActive = !mStatistics.isActive;

			if (event.key.code == sf::Keyboard::Escape)
				mWindow.close();
		}

		if (event.type == sf::Event::Closed)
		{
			mWindow.close();
		}
	}
}

void Game::loadResources()
{
	// FONT-HOLDER
	mFontHolder.loadResource(Fonts::Statistics, "Media/Fonts/OpenSans-Bold.ttf");
	mStatistics.Text.setFont(mFontHolder.getResource(Fonts::Statistics));

	// TEXTURE-HOLDER
	mTextureHolder.loadResource(Textures::Eagle, "Media/Textures/Eagle.png");
	mTextureHolder.loadResource(Textures::Raptor, "Media/Textures/Raptor.png");
	mTextureHolder.loadResource(Textures::Landscape, "Media/Textures/Desert.png");
}