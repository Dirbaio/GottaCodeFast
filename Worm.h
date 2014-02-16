#ifndef WORM_H
#define WORM_H
#include "Monster.h"
#include "tools.hpp"

class Worm : public Monster
{
	private:
		int frame, nFrames, estado, d, repeticiones;
		float timeFrame;
	public:
		Worm();
		virtual void update(float deltaTime);
		virtual bool isClicked(sf::Vector2f pos);
		virtual void die();
};

#endif // WORM_H
