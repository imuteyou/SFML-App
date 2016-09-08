#ifndef STATE_HPP

#define STATE_HPP


#include "StateIdentifiers.hpp"


#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>


#include <memory>


class StateStack;

class State
{
public:
	typedef std::unique_ptr<State>			Ptr;

	struct Context
	{

	};

public:
											State(StateStack & stack, Context context);
	virtual									~State();

	virtual void							draw() = 0;
	virtual bool							update(sf::Time deltaT) = 0;
	virtual bool							handleEvent(const sf::Event & event) = 0;

protected:
	void									requestStackPush(States::ID stateID);
	void									requestStackPop();
	void									requestStateClear();

private:
	StateStack*								mStack;
	Context									mContext;
};

#endif // !STATE_HPP
