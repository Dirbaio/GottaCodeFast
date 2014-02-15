#include "Worm.h"

Worm::Worm(){
	speed = 50;
	estado = 0;
	nEstados = 13;
	d = 1;
	timeFrame = 1.f/26.f;
	loadTexture();

	this->setPosition(sf::Vector2f(100,100));
	posFinal = sf::Vector2f(300,100);

}

void Worm::loadTexture(){
	texture.loadFromFile("data/gusanito.png");
	this->setTexture(texture);
}

void Worm::update(float deltaTime) {
	float s = deltaTime * speed;
	float distx = posFinal.x-getPosition().x;
	float disty = posFinal.y-getPosition().y;
	float sqrt = std::sqrt(distx*distx + disty*disty);
	sf::Vector2f director = sf::Vector2f(distx/sqrt,disty/sqrt);
	this->setPosition(this->getPosition()+director*s);

	timeFrame -= deltaTime;
	if (timeFrame < 0.f) {
		estado += d;
		timeFrame += 1.f/26.f;
	}
	if (estado >= nEstados) {
		d = -1;
		estado = nEstados-2;
	}
	else if (estado < 0) {
		d = 1;
		estado = 1;
	}
	this->setTextureRect(sf::IntRect(sf::Vector2i(estado*100,0),sf::Vector2i(100,63)));
}
