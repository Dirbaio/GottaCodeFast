#include "Spider.h"
#include "Resources.hpp"

Spider::Spider() {
	speed = 25;
	alive = true;
	waiting = false;

	estado = 0; // 0 caminando, 1 comiendo, 2 muriendo
	frame = 0;
	nFrames = 11;
	timeFrame = 3.f/11.f;

	repeticiones  = 3;

	this->setTexture(Resources::spider);

	this->setPosition(sf::Vector2f(500,100));
	posFinal = sf::Vector2f(500,800);
}

void Spider::update(float deltaTime) {

	if (estado != 2 and !waiting) {

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
			frame += 1;
			if (estado == 0) timeFrame += 2.f/11.f;
			else if (estado == 1) timeFrame += 3.f/11.f;
		}
		if (frame >= nFrames) {
			frame = 0;
		}
		this->setTextureRect(sf::IntRect(sf::Vector2i(frame*200,estado*150),sf::Vector2i(200,150)));
	}
	else if (waiting) this->setTextureRect(sf::IntRect(sf::Vector2i(200,0),sf::Vector2i(100,63)));
	else {
		timeFrame -= deltaTime;
		if (timeFrame < 0.f) {
			frame += 1;
			timeFrame += 2.f/26.f;
		}
		if (frame >= nFrames) alive = false;
		this->setTextureRect(sf::IntRect(sf::Vector2i(frame*100,estado*63),sf::Vector2i(100,63)));
	}
}

bool Spider::isClicked(sf::Vector2f pos){
	if (1) {
		die();
		return true;
	}
	return false;
}

void Spider::die() {
	estado = 2;
	d = 1;
	frame = 0;
	timeFrame = 2.f/26.f;
}

