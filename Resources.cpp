#include "Resources.hpp"

void Resources::load()
{
	font.loadFromFile("data/Monospace.ttf");
	messageFont.loadFromFile("data/Frijole-Regular.ttf");
	happy.loadFromFile("data/happy.png");
	sad.loadFromFile("data/sad.png");
	troll.loadFromFile("data/troll.png");
}
