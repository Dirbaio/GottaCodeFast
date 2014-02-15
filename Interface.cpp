#include "Interface.hpp"
#include "GottaCodeFast.hpp"

Interface::Interface(GottaCodeFast* game) : game(game) {
	init();
}

void Interface::init() {
	fondo.loadFromFile("data/background.jpg");
	background.setTexture(fondo);

	sf::Vector2u s = game->getWindow().getSize();

	float scaleX = fondo.getSize().x/float(s.x);
	float scaleY = fondo.getSize().y/float(s.y);

	background.setScale(scaleX,scaleY);
	background.setPosition(sf::Vector2f(0,0));
}

void Interface::draw() {
	game->getWindow().draw(background);
}

void Interface::update(float deltaTime) {
}
