#include "Interface.hpp"
#include "GottaCodeFast.hpp"

Interface::Interface(GottaCodeFast* game) : game(game) {
	//BACKGROUND
	fondo.loadFromFile("data/background.jpg");
	background.setTexture(fondo);
	sf::Vector2u s = game->getWindow().getSize();
	float scaleX = float(s.x)/fondo.getSize().x;
	float scaleY = float(s.y)/fondo.getSize().y;
	background.setScale(scaleX,scaleY);
	background.setPosition(sf::Vector2f(0,0));
	//TIMER BAR
	timerBack = sf::RectangleShape(sf::Vector2f(100,800));
	timerBack.setPosition(100,100);
	timerBack.setFillColor(sf::Color(50,50,50));
	timerFront = sf::RectangleShape(sf::Vector2f(90,-790));
	timerFront.setPosition(105,895);
	timerFront.setFillColor(sf::Color(200,200,200));

	//PUNTUACION
	int punt = 10;//game->getPuntuacion();
	puntuacion = sf::Text(std::to_string(punt),game->getFont(),50);
	sf::FloatRect textRect = puntuacion.getLocalBounds();
	puntuacion.setOrigin(textRect.left + textRect.width/2.0f,
						 textRect.top  + textRect.height/2.0f);
	puntuacion.setPosition(sf::Vector2f(s.x/2.0f,s.y/14.0f));
}

void Interface::draw() {
	//game->getWindow().draw(background);
	game->getWindow().draw(puntuacion);
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
