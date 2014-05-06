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




int main()
{
    sf::RenderWindow window;
    window.create(sf::VideoMode::getFullscreenModes()[0], "PRO1: The Game" , sf::Style::Default);
    window.setMouseCursorVisible(true);
    window.setVerticalSyncEnabled(true);

    Resources::load();

    Problem p ("parell");
    GottaCodeFast gcf(window, p);

    sf::Clock c;
    srand(time(0));
    while(window.isOpen())
    {
        float deltaTime = c.restart().asSeconds();
        gcf.update(deltaTime);
        window.clear();
        gcf.draw();
        window.display();
    }
}
