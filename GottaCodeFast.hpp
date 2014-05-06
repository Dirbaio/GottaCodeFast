#ifndef GOTTACODEFAST_HPP
#define GOTTACODEFAST_HPP
#include "Editor.hpp"
#include "Interface.hpp"
#include "Worm.h"
#include "Spider.h"
#include "Keyboard.hpp"
#include "Problem.hpp"

class Player;
class GottaCodeFast {
	public:
        GottaCodeFast(sf::RenderWindow& window, Problem prob);
		~GottaCodeFast();

		void update(float deltaTime);
		void draw();

		std::string problem;
		bool done;

        sf::RenderWindow& getWindow() { return window; }

        sf::RenderWindow& window;
        Problem prob;
		void addRandomWorm();
		float doneTime;
		float time;
		bool timeUp;
		Interface ui;
		std::vector<Monster*> monsters;
		std::vector<sf::Vector2u> monstersObjective;

        std::vector<Player*> players;
};

#endif // GOTTACODEFAST_HPP
