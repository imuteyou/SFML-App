#include "StateStack.hpp"

#include <cassert>

State::Ptr StateStack::createState(States::ID stateID)
{
	auto found = mFactories.find(stateID);
	assert(found != mFactories.end());
	return found->second();
}
