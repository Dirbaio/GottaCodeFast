#ifndef GAME_HPP
#define GAME_HPP
#include "tools.hpp"

class Game {
	public:
		Game(int scrwidth, int scrheight, std::string title, int style);
		virtual ~Game();

		void run();
		void processInput();

		virtual void update(float deltaTime) = 0;
		virtual void draw() = 0;

		virtual void onKeyPressed(sf::Event event) = 0;
		virtual void onMouseButtonPressed(sf::Event event) = 0;

		sf::RenderWindow& getWindow() { return window;}

	protected:
		sf::RenderWindow window;
};

#endif // GAME_HPP
