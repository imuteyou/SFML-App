#ifndef COMMAND_HPP

#define COMMAND_HPP

#include "Category.hpp"


#include <SFML/System/Time.hpp>


#include <functional>


class SceneNode;

struct Command
{
													Command();

	std::function<void(SceneNode&, sf::Time)>		action;
	unsigned int									category;
};

#endif // !COMMAND_HPP
