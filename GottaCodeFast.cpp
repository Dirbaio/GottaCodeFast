#include "GottaCodeFast.hpp"

GottaCodeFast::GottaCodeFast(int scrwidth, int scrheight, std::string title, int style) : Game(scrwidth, scrheight, title, style), editor(this), ui(this) {
}

GottaCodeFast::~GottaCodeFast() {
}

void GottaCodeFast::update(float deltaTime) {
	editor.update(deltaTime);
}

void GottaCodeFast::draw() {
	editor.draw(sf::Vector2f(100,100));
	//ui.draw();
}

void GottaCodeFast::onMouseButtonPressed(sf::Event event) {
}

void GottaCodeFast::onKeyPressed(int key) {
	std::cout<<key<<" "<<char(key)<<std::endl;

	if(key == 27)
		window.close();
	else
		editor.process(key);

	/*
	switch(event.key.code) {
		case sf::Keyboard::Escape:
			window.close();
			break;
		case sf::Keyboard::BackSpace:
			editor.del();
			break;
		case sf::Keyboard::Return:
			editor.newline();
			break;
		case sf::Keyboard::Right:
			editor.forward();
			break;
		case sf::Keyboard::Left:
			editor.backward();
			break;
		case sf::Keyboard::Up:
			editor.up();
			break;
		case sf::Keyboard::Down:
			editor.down();
			break;
		default:
			break;
	}
	editor.process(event);*/
}

