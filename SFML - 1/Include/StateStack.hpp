#ifndef STATESTACK_HPP

#define STATESTACK_HPP


#include "StateIdentifiers.hpp"
#include "State.hpp"


#include <SFML/System/NonCopyable.hpp>


#include <vector>
#include <map>
#include <functional>


class StateStack
	: private sf::NonCopyable
{
public:
	enum Action
	{
		Push,
		Pop,
		Clear,
	};

public:
	explicit												StateStack(State::Context context);

	template<typename T>
	void													registerState(States::ID stateID);
	void													update(sf::Time deltaT);
	void													draw();
	void													handleEvent(const sf::Event & event);
		
	void													pushState(States::ID stateID);
	void													popState();
	void													clearStates();
	bool													isEmpty() const;

private:
	struct PendingChange
	{
		Action												action;
		States::ID											stateID;
	};

	std::vector<State::Ptr>									mStack;
	std::vector<PendingChange>								mPendingChangesList;
	std::map < States::ID, std::function<State::Ptr()> >	mFactories;
	State::Context											mContext;

private:
	State::Ptr												createState(States::ID stateID);
	void													applyPendingChanges();
};	


template <typename T>
void StateStack::registerState(States::ID stateID)
{
	mFactories[stateID] = [this]()
	{
		return State::Ptr(new T(*this));
	}
}

#endif // !STATESTACK_HPP
