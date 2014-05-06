#include "GottaCodeFast.hpp"
#include "Player.hpp"


GottaCodeFast::GottaCodeFast(sf::RenderWindow& window, Problem prob)
    : window(window), prob(prob), ui(this)
{

    timeUp = false;
	time = 0.9;
	done = false;
	doneTime = 10;

    int playerCount = 2;
    players.resize(playerCount);
    for(int i = 0; i < playerCount; i++)
    {
        players[i] = new Player(i, *this);
    }
}

GottaCodeFast::~GottaCodeFast() {
}

void GottaCodeFast::addRandomWorm() {
//    Worm* w = new Worm();
//    sf::Vector2u editorPos = editor.getRandomCharPos();
//    w->setPosFinal(sf::Vector2f(editorPos.x, editorPos.y));
//    w->setPosition(sf::Vector2f(std::rand() % 2 == 0 ? 0.0f : window.getSize().x,editorPos.y));
//    monsters.push_back(w);
//    monstersObjective.push_back();
}

void GottaCodeFast::update(float deltaTime) {

    for(int i = 0; i < (int)players.size(); i++)
        players[i]->update(deltaTime);

	ui.update(deltaTime);

	if(ui.timeUp() && !timeUp && !done && time > 4.01)
	{
		timeUp = true;
//		ui.setMessage("Tiempo!", 2, sf::Color(255, 200, 0));
		doneTime = 2;
	}

	if(doneTime < 9)
	{
		doneTime -= deltaTime;
		if(doneTime < 0)
			window.close();
	}
}

void GottaCodeFast::draw() {
	ui.draw();
    for(int i = 0; i < (int)players.size(); i++)
        players[i]->draw();

    for(unsigned int i = 0; i < monsters.size(); ++i) window.draw(*monsters[i]);
}



