#include "Game.hpp"

Game::Game(int scrwidth, int scrheight, std::string title, int style) {
	window.create(sf::VideoMode(scrwidth,scrheight,32), title , style);
	window.setMouseCursorVisible(true);
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
                onKeyPressed(RIGHT_KEY);
                break;
            case sf::Keyboard::Left:
                onKeyPressed(LEFT_KEY);
                break;
            case sf::Keyboard::Up:
                onKeyPressed(UP_KEY);
                break;
            case sf::Keyboard::Down:
                onKeyPressed(DOWN_KEY);
                break;
            case sf::Keyboard::Home:
                onKeyPressed(HOME_KEY);
                break;
            case sf::Keyboard::End:
                onKeyPressed(END_KEY);
                break;
            case sf::Keyboard::F5:
                onKeyPressed(F5_KEY);
                break;
            case sf::Keyboard::LControl:
            case sf::Keyboard::RControl:
                onKeyPressed(CONTROL_KEY);
                break;
            case sf::Keyboard::LShift:
            case sf::Keyboard::RShift:
                onKeyPressed(SHIFT_KEY);
                break;
            case sf::Keyboard::Return:
                onKeyPressed(RETURN_KEY);
                break;
            case sf::Keyboard::Delete:
                onKeyPressed(DELETE_KEY);
                break;
            case sf::Keyboard::Tab:
                onKeyPressed(TAB_KEY);
                break;
            default:
                break;
            }
            break;

        case sf::Event::KeyReleased:
            switch(event.key.code) {
            case sf::Keyboard::LControl:
            case sf::Keyboard::RControl:
                onKeyReleased(CONTROL_KEY);
                break;
            case sf::Keyboard::LShift:
            case sf::Keyboard::RShift:
                onKeyReleased(SHIFT_KEY);
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
