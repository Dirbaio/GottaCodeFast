#include "GottaCodeFast.hpp"
#include "Resources.hpp"

int main() {
	Resources::load();
	GottaCodeFast game(sf::VideoMode::getFullscreenModes()[0].width,sf::VideoMode::getFullscreenModes()[0].height,"GottaCodeFast",sf::Style::Default);
	game.run();
	return 42;
}

