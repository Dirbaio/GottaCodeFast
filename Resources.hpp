#ifndef RESOURCES_HPP
#define RESOURCES_HPP
#include "tools.hpp"

class Resources
{
	public:
		static sf::Font font;
		static sf::Font messageFont;
		static sf::Texture happy;
		static sf::Texture sad;
		static sf::Texture troll;
		static sf::Texture worm;
		static sf::Texture spider;
		static void load();
};

#endif // RESOURCES_HPP
