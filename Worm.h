#ifndef WORM_H
#define WORM_H
#include "Monster.h"
#include "tools.hpp"

class Worm : public Monster
{
	private:
		int frame, nFrames, estado, d, repeticiones;
		float timeFrame;
		bool comido;
	public:
		Worm();
		virtual void update(float deltaTime);
		virtual bool isClicked(sf::Vector2f pos);
		virtual void die();
		virtual void setPosFinal(sf::Vector2f d);
};

#endif // WORM_H
