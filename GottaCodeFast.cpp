#include "GottaCodeFast.hpp"

GottaCodeFast::GottaCodeFast() : ui(this) {
}

GottaCodeFast::~GottaCodeFast() {
}

void GottaCodeFast::update(float deltaTime) {
}

void GottaCodeFast::draw() {
	ui.draw();
}

void GottaCodeFast::onKeyPressed(sf::Event event) {
	if (event.key.code == sf::Keyboard::Escape) window.close();
}

void GottaCodeFast::onMouseButtonPressed(sf::Event event) {
}

