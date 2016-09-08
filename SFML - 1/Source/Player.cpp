#include "Player.hpp"



#include <iostream>



Player::Player()
{
	mKeyBinding[sf::Keyboard::Left] = MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = MoveRight;
	mKeyBinding[sf::Keyboard::Up] = MoveUp;
	mKeyBinding[sf::Keyboard::Down] = MoveDown;

	initializeActions();

	for(auto & pair : mActionBinding)
		pair.second.category = Category::PlayerAircraft;
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
	for (auto iterator = mKeyBinding.begin(); iterator != mKeyBinding.end();)
	{
		if (iterator->second == action)
			mKeyBinding.erase(iterator++);
		else
			iterator++;
	}

	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
	for (auto pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::handleEvent(const sf::Event & event, CommandQueue & commands)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
	{
		Command output;
		output.category = Category::PlayerAircraft;
		output.action = [](SceneNode & node, sf::Time)
		{
			std::cout << node.getPosition().x << " " << node.getPosition().y << "\n";
		};
		commands.push(output);
	}
}


void Player::handleRealTimeInput(CommandQueue & commands)
{
	for (auto pair : mKeyBinding)
	{
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

bool Player::isRealTimeAction(Action action)
{
	switch (action)
	{
		case MoveLeft:
			return true;
		case MoveRight:
			return true;
		case MoveDown:
			return true;
		case MoveUp:
			return true;

		default:
			return false;
	}
}

void Player::initializeActions()
{
	const float playerSpeed = 200.f;

	mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-playerSpeed, 0.f));
	mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+playerSpeed, 0.f));
	mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
	mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
}

