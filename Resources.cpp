#include "Resources.hpp"

sf::Font Resources::font;
sf::Font Resources::messageFont;
sf::Image Resources::happy;
sf::Image Resources::sad;
sf::Image Resources::troll;


void Resources::load()
{
	font.loadFromFile("data/Monospace.ttf");
	messageFont.loadFromFile("data/Frijole-Regular.ttf");
	happy.loadFromFile("data/happy.png");
	sad.loadFromFile("data/sad.png");
	troll.loadFromFile("data/troll.png");
}
