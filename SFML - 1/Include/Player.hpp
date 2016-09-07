#ifndef PLAYER_HPP

#define PLAYER_HPP

#include "CommandQueue.hpp"
#include "Aircraft.hpp"

#include <SFML/Window/Event.hpp>



struct AircraftMover
{
	AircraftMover(float vx, float vy)
		: velocity(vx, vy)
	{
	}


	void operator() (Aircraft & aircraft, sf::Time time) const
	{
		aircraft.addVelocity(velocity);
	}


	sf::Vector2f velocity;
};




class Player
{
public:
	enum Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
	};

public:
										Player();
	void								assignKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key					getAssignedKey(Action action) const;
	void								handleEvent(const sf::Event & event, CommandQueue & commands);
	void								handleRealTimeInput(CommandQueue & commands);

private:
	std::map<sf::Keyboard::Key, Action> mKeyBinding;
	std::map<Action, Command>			mActionBinding;

private:
	static bool							isRealTimeAction(Action action);
	void								initializeActions();
};



#endif