#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>



#include "Game.hpp"
#include "StringHelpers.hpp"

const sf::Time Game::timePerFrame = sf::seconds(1.0f / 600.0f);

Game::Game()
	: mWindow(sf::VideoMode(1920, 1080), "SFML-APP")
	, mTextureHolder()
	, mFontHolder()
	, mWorld(mWindow)
	, mIsActive(true)
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
		processInput();
		sf::Time elapsedTime = clock.restart();

		if(mIsActive)
			timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > timePerFrame  && mIsActive)
		{
			processInput();
			update(timePerFrame);

			timeSinceLastUpdate -= timePerFrame;
		}
		render();
	}

}

void Game::render()
{
	mWindow.clear();
	mWorld.draw();
	mWindow.setView(mWindow.getDefaultView());

	if(mStatistics.isActive)
		mWindow.draw(mStatistics.Text);

	mWindow.display();
}

void Game::update(sf::Time deltaT)
{
	mWorld.update(deltaT);
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
	sf::Event event;

	while (mWindow.pollEvent(event))
	{
		mPlayer.handleEvent(event, mCommandQueue);
		handleUtilityEvent(event);

		if (event.type == sf::Event::Closed)
			mWindow.close();
	}

	mPlayer.handleRealTimeInput(mCommandQueue);
}


void Game::handleUtilityEvent(sf::Event event)
{
	mWindow.setKeyRepeatEnabled(false);

	switch (event.type)
	{	
		case sf::Event::KeyPressed:
			if(event.key.code == sf::Keyboard::F3)
				mStatistics.isActive = !mStatistics.isActive;
			break;

		case sf::Event::LostFocus:
			mIsActive = false;
			break;

		case sf::Event::GainedFocus:
			mIsActive = true;
			break;

		default:
			break;
	}

	mWindow.setKeyRepeatEnabled(true);
}

void Game::loadResources()
{
	// FONT-HOLDER
	mFontHolder.loadResource(Fonts::Statistics, "Media/Fonts/OpenSans-Bold.ttf");
	mStatistics.Text.setFont(mFontHolder.getResource(Fonts::Statistics));
}
