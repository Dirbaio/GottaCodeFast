#include "GottaCodeFast.hpp"

int main() {
	GottaCodeFast game(sf::VideoMode::getFullscreenModes()[0].width-100,sf::VideoMode::getFullscreenModes()[0].height-100,"GottaCodeFast",sf::Style::Default);
	game.run();
	return 42;
}

