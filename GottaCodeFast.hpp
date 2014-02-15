#ifndef GOTTACODEFAST_HPP
#define GOTTACODEFAST_HPP
#include "Game.hpp"
#include "Editor.hpp"
#include "Interface.hpp"

class GottaCodeFast : public Game {
	public:
		GottaCodeFast(int scrwidth, int scrheight, std::string title, int style);
		~GottaCodeFast();

		void update(float deltaTime);
		void draw();

		void onKeyPressed(sf::Event event);
		void onMouseButtonPressed(sf::Event event);

	private:
		Editor editor;
		Interface ui;
};

#endif // GOTTACODEFAST_HPP
