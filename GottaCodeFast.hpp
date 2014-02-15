#ifndef GOTTACODEFAST_HPP
#define GOTTACODEFAST_HPP
#include "Game.hpp"
#include "Interface.hpp"

class GottaCodeFast : public Game {
	public:
		GottaCodeFast();
		~GottaCodeFast();

		void update(float deltaTime);
		void draw();

		void onKeyPressed(sf::Event event);
		void onMouseButtonPressed(sf::Event event);

	private:
		Interface ui;

};

#endif // GOTTACODEFAST_HPP
