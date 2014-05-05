#ifndef GOTTACODEFAST_HPP
#define GOTTACODEFAST_HPP
#include "Game.hpp"
#include "Editor.hpp"
#include "Interface.hpp"
#include "Worm.h"
#include "Spider.h"

class GottaCodeFast : public Game {
	public:
		GottaCodeFast(std::string problem, int scrwidth, int scrheight, std::string title, int style);
		~GottaCodeFast();

		void update(float deltaTime);
		void draw();
		void compile();
		void compilationFinished(int status, std::string errors);
		void onKeyPressed(int key);
		void onMouseButtonPressed(sf::Event event);

		std::string problem;
		bool done;
	private:
		float doneTime;
		float time;
		bool timeUp;
		int timeLimit;
		Editor editor;
		Interface ui;
		bool compiling;
		int pid;
		int errorfd;
		std::string output;
};

#endif // GOTTACODEFAST_HPP
