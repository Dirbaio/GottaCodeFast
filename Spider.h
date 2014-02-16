#ifndef SPIDER_H
#define SPIDER_H
#include "Monster.h"
#include "tools.hpp"

class Spider : public Monster
{
	private:
		int frame, nFrames, estado, repeticiones;
		float timeFrame;
		bool comido;
	public:
		Spider();
		virtual void update(float deltaTime);
		virtual bool isClicked(sf::Vector2f pos);
		virtual void die();
};

#endif // SPIDER_H
