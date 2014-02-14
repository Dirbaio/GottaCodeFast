#include "GottaCodeFast.hpp"

int main() {
	GottaCodeFast game;
	game.init(sf::VideoMode::getFullscreenModes()[0].width-100,sf::VideoMode::getFullscreenModes()[0].height-100,"TITLE",sf::Style::Default);
	game.run();
	return 42;
}

