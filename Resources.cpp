#include "Resources.hpp"

sf::Font Resources::font;
sf::Font Resources::messageFont;
sf::Texture Resources::happy;
sf::Texture Resources::sad;
sf::Texture Resources::troll;
sf::Texture Resources::worm;
sf::Texture Resources::spider;
sf::Texture Resources::background;


void Resources::load()
{
    background.loadFromFile("data/background2.png");
	font.loadFromFile("data/Monospace.ttf");
	messageFont.loadFromFile("data/Frijole-Regular.ttf");
	happy.loadFromFile("data/happy.png");
	sad.loadFromFile("data/sad.png");
	troll.loadFromFile("data/troll.png");
	worm.loadFromFile("data/gusanito.png");
	spider.loadFromFile("data/spider.png");
}
