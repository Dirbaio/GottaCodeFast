#include "GottaCodeFast.hpp"

GottaCodeFast::GottaCodeFast(int scrwidth, int scrheight, std::string title, int style) : Game(scrwidth, scrheight, title, style), editor(this), ui(this) {
}

GottaCodeFast::~GottaCodeFast() {
}

void GottaCodeFast::update(float deltaTime) {
	editor.update(deltaTime);
}

void GottaCodeFast::draw() {
	editor.draw();
	ui.draw();
}

void GottaCodeFast::onKeyPressed(sf::Event event) {
	if (event.key.code == sf::Keyboard::Escape) window.close();
}

void GottaCodeFast::onMouseButtonPressed(sf::Event event) {
}

