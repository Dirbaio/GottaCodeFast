#include "Worm.h"
#include "Resources.hpp"

Worm::Worm(){
	speed = 50;
	alive = true;
	waiting = false;
	comido = false;

	estado = 0; // 0 caminando, 1 comiendo, 2 muriendo
	frame = 0;
	nFrames = 13;
	d = 1;
	timeFrame = 1.f/26.f;

	repeticiones  = 2;

	this->setTexture(Resources::worm);
	this->setOrigin(sf::Vector2f(40,31));
}

void Worm::update(float deltaTime) {
	if (getPosition().x > posFinal.x) this->setScale(-1,1);

	if (!(estado == 2 or waiting)) {

		float distx = posFinal.x-getPosition().x;
		float disty = posFinal.y-getPosition().y;

		if (std::abs(distx) < 5 and std::abs(disty) < 5  and estado == 0) {
			estado = 1;
			frame = 0;
		}
		else if (estado != 2) {
			float s = deltaTime * speed;

			float sqrt = std::sqrt(distx*distx + disty*disty);
			sf::Vector2f director = sf::Vector2f(distx/sqrt,disty/sqrt);
			this->setPosition(this->getPosition()+director*s);
		}

		timeFrame -= deltaTime;
		if (timeFrame < 0.f) {
			frame += d;
			if (estado == 0) timeFrame += 1.f/26.f;
			else if (estado == 1) timeFrame += 0.5f/26.f;
		}
		if (frame >= nFrames) {
			d = -1;
			frame = nFrames-2;
		}
		else if (frame < 0) {
			d = 1;
			frame = 1;
			if (estado == 1) --repeticiones;
			if (estado == 1 and repeticiones == 0) {
				comido = true;
				waiting = true;
			}
		}
		this->setTextureRect(sf::IntRect(sf::Vector2i(frame*100,estado*63),sf::Vector2i(100,63)));
	}
	else if (waiting and estado != 2) this->setTextureRect(sf::IntRect(sf::Vector2i(200,0),sf::Vector2i(100,63)));
	else {
		timeFrame -= deltaTime;
		if (timeFrame < 0.f) {
			frame += d;
			timeFrame += 2.f/26.f;
		}
		if (frame >= nFrames) alive = false;
		this->setTextureRect(sf::IntRect(sf::Vector2i(frame*100,estado*63),sf::Vector2i(100,63)));
	}
}

bool Worm::isClicked(sf::Vector2f pos){
	if (alive and std::abs(pos.x - (getPosition().x)) < 40 and std::abs(pos.y - getPosition().y) < 31) {
		die();
		return true;
	}
	return false;
}

void Worm::die() {
	estado = 2;
	d = 1;
	frame = 0;
	timeFrame = 2.f/26.f;
}

void Worm::setPosFinal(sf::Vector2f d) {
	posFinal = d;
	comido = false;
}
