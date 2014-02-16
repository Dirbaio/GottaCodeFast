#ifndef GOTTACODEFAST_HPP
#define GOTTACODEFAST_HPP
#include "Game.hpp"
#include "Editor.hpp"
#include "Interface.hpp"
#include "Worm.h"
#include "Spider.h"

class GottaCodeFast : public Game {
	public:
		GottaCodeFast(int scrwidth, int scrheight, std::string title, int style);
		~GottaCodeFast();

		void update(float deltaTime);
		void draw();
		void compile();
		void compilationFinished(int status, std::string errors);
		void onKeyPressed(int key);
		void onMouseButtonPressed(sf::Event event);

		std::string problem;

	private:
		float time;
		bool timeUp;

		Editor editor;
		Interface ui;
		bool compiling;
		int pid;
		int errorfd;
		std::string output;
		Worm w;
		Spider s;
};

#endif // GOTTACODEFAST_HPP
