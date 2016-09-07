#ifndef GAME_HPP

#define GAME_HPP

#include "Player.hpp"
#include "ResourceHolder.hpp"
#include "World.hpp"
#include "ResourceIdentifiers.hpp"


#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>



class Game
{
public:
								Game();
	void						run();

private:
	void						render();
	void						update(sf::Time deltaT);
	void						updateStatistics(sf::Time deltaT);
	void						processInput();
	void						handleUtilityEvent(sf::Event event);
	void						loadResources();

private:
	static const sf::Time		timePerFrame;
	sf::RenderWindow			mWindow;
	TextureHolder				mTextureHolder;
	FontHolder					mFontHolder;
	CommandQueue				mCommandQueue;
	World						mWorld;
	Player						mPlayer;
	bool						mIsActive;

private:
	struct						statistics
	{
		bool						isActive = false;
		float						NumberOfFrames = 0;
		sf::Time					UpdateTime = sf::Time::Zero;
		sf::Text					Text;
	};

	statistics					mStatistics;
};


#endif