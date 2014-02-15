#include "Game.hpp"

Game::Game(int scrwidth, int scrheight, std::string title, int style) {
	window.create(sf::VideoMode(scrwidth,scrheight,32), title , style);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(false);
}

Game::~Game() {
}

void Game::processInput() {
	sf::Event event;
	while(window.pollEvent(event)) {
		switch(event.type){
			case sf::Event::MouseButtonPressed:
				onMouseButtonPressed(event);
				break;
			case sf::Event::KeyPressed:
				onKeyPressed(event);
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
		}
	}
}

void Game::run() {
	sf::Clock c;
	srand(time(0));
	while(window.isOpen()) {
		float deltaTime = c.restart().asSeconds();
		processInput();
		update(deltaTime);
		window.clear();
		draw();
		window.display();
	}
}
