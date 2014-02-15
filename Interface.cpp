#include "Interface.hpp"
#include "GottaCodeFast.hpp"

Interface::Interface(GottaCodeFast* game) : game(game) {
	init();
}

void Interface::init() {
	//BACKGROUND
	fondo.loadFromFile("data/background.jpg");
	background.setTexture(fondo);
	sf::Vector2u s = game->getWindow().getSize();
	float scaleX = float(s.x)/fondo.getSize().x;
	float scaleY = float(s.y)/fondo.getSize().y;
	background.setScale(scaleX,scaleY);
	background.setPosition(sf::Vector2f(0,0));
	//TIMER BAR
	//sf::RectangleShape timerBack(sf::Vector2f());
	float espacioSobrante = 100;
	tTotal  = tParcial = 100.0f;//game->getTiempoNivel();
	tiempo.setTexture(fondo);
	scaleX = 0.01*float(s.x)/fondo.getSize().x;
	scaleY = (float(s.y)-espacioSobrante)/fondo.getSize().y;
	tiempo.setScale(scaleX,scaleY);
	sf::FloatRect rect = tiempo.getLocalBounds();
	tiempo.setOrigin(rect.left + rect.width/2.0f,
						 rect.top  + rect.height);
	tiempo.setPosition(sf::Vector2f(game->getWindow().getSize().x - 150, game->getWindow().getSize().y - espacioSobrante/2.f));
	//PUNTUACION
	fuente.loadFromFile("data/Monospace.ttf");
	int punt = 10;//game->getPuntuacion();
	puntuacion = sf::Text(std::to_string(punt),fuente);
	sf::FloatRect textRect = puntuacion.getLocalBounds();
	puntuacion.setOrigin(textRect.left + textRect.width/2.0f,
						 textRect.top  + textRect.height/2.0f);
	puntuacion.setPosition(sf::Vector2f(s.x/2.0f,s.y/14.0f));
}

void Interface::draw() {
	game->getWindow().draw(background);
	game->getWindow().draw(puntuacion);
	game->getWindow().draw(tiempo);
}

void Interface::update(float deltaTime) {
	tParcial -= deltaTime;
	float porcentaje = tParcial/tTotal;
	puntuacion.setScale(tiempo.getScale().x, porcentaje*(float(game->getWindow().getSize().y)-100)/fondo.getSize().y);
}
