#include "Interface.hpp"
#include "GottaCodeFast.hpp"
#include "Resources.hpp"

Interface::Interface(GottaCodeFast* game) : game(game) {
	//BACKGROUND
    background.setTexture(Resources::background);
    sf::Vector2u s = game->getWindow().getSize();
    float scaleX = float(s.x)/Resources::background.getSize().x;
    float scaleY = float(s.y)/Resources::background.getSize().y;
    background.setScale(scaleX, scaleY);
	background.setPosition(sf::Vector2f(0,0));

	//TIMER BAR
	timerBack = sf::RectangleShape(sf::Vector2f(100,800));
    int xx = 912;
    timerBack.setPosition(xx,100);
	timerBack.setFillColor(sf::Color(50,50,50));
	timerFront = sf::RectangleShape(sf::Vector2f(90,-790));
    timerFront.setPosition(xx+5,895);
	timerFront.setFillColor(sf::Color(200,200,200));

	problem = sf::Text("", Resources::messageFont, 30);

    problem.setPosition(sf::Vector2f(250.0f,40.0f));

	resetTime(100000000);
}

void Interface::setStatement(std::string s)
{
	problem.setString(s);
}

void Interface::draw() {
	game->getWindow().draw(background);
	game->getWindow().draw(problem);
	game->getWindow().draw(tiempo);
	game->getWindow().draw(timerBack);
	game->getWindow().draw(timerFront);


}

void Interface::update(float deltaTime) {
	tParcial = std::fmax(tParcial-deltaTime,0);
	float porcentaje = tParcial/tTotal;
	timerFront.setSize(sf::Vector2f(timerFront.getSize().x,porcentaje*-790.0f));
}

void Interface::resetTime(float t) {
	tTotal = t;
	tParcial = t;
}
