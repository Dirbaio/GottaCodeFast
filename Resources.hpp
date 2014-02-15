#ifndef RESOURCES_HPP
#define RESOURCES_HPP
#include "tools.hpp"

class Resources
{
	public:
		static sf::Font font;
		static sf::Font messageFont;
		static sf::Image happy;
		static sf::Image sad;
		static sf::Image troll;
		static void load();
};

#endif // RESOURCES_HPP
