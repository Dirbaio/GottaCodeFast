#include "Game.hpp"

Game::Game(int scrwidth, int scrheight, std::string title, int style) {
	window.create(sf::VideoMode(scrwidth,scrheight,32), title , style);
	window.setMouseCursorVisible(false);
	window.setVerticalSyncEnabled(true);
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
				switch(event.key.code) {
					case sf::Keyboard::Right:
						onKeyPressed(1);
						break;
					case sf::Keyboard::Left:
						onKeyPressed(2);
						break;
					case sf::Keyboard::Up:
						onKeyPressed(3);
						break;
					case sf::Keyboard::Down:
						onKeyPressed(4);
						break;
					case sf::Keyboard::F5:
						onKeyPressed(5);
						break;
					default:
						break;
				}
				break;
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::TextEntered:
				onKeyPressed(event.text.unicode);
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
