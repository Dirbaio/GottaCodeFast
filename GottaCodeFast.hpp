#ifndef GOTTACODEFAST_HPP
#define GOTTACODEFAST_HPP
#include "Game.hpp"
#include "Editor.hpp"

class GottaCodeFast : public Game {
	public:
		GottaCodeFast();
		~GottaCodeFast();

		void doInit();
		void update(float deltaTime);
		void draw();

		void onKeyPressed(sf::Event event);
		void onMouseButtonPressed(sf::Event event);

	private:
		Editor editor;
};

#endif // GOTTACODEFAST_HPP
