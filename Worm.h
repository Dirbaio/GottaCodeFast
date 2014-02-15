#ifndef WORM_H
#define WORM_H
#include "Monster.h"
#include "tools.hpp"

class Worm : public Monster
{
	private:
		int estado,nEstados,d;
		float timeFrame;
	public:
		Worm();
		virtual void loadTexture();
		virtual void update(float deltaTime);

};

#endif // WORM_H
