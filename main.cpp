#include "GottaCodeFast.hpp"
#include "Resources.hpp"

std::string problems[] = {
    "parell",
    "factorial",
    "helloworld",
    "42",
	"sum",
	"max",
	"addonesecond",
    "fibonacci",
    "END"
};

int main() {
	Resources::load();

	int pbmNum = 0;

	while(true)
	{
		GottaCodeFast game(problems[pbmNum], sf::VideoMode::getFullscreenModes()[0].width,sf::VideoMode::getFullscreenModes()[0].height,"GottaCodeFast",sf::Style::Default);
		game.run();

		if(game.done)
			pbmNum++;

		if(problems[pbmNum] == "END")
			break;
	}

	return 0;
}

