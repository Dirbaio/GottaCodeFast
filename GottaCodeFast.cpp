#include "GottaCodeFast.hpp"

GottaCodeFast::GottaCodeFast() : editor(this) {
}

GottaCodeFast::~GottaCodeFast() {
}

void GottaCodeFast::doInit() {
}

void GottaCodeFast::update(float deltaTime) {
	editor.update(deltaTime);
}

void GottaCodeFast::draw() {
	editor.draw();
}

void GottaCodeFast::onKeyPressed(sf::Event event) {
    if (event.key.code == sf::Keyboard::Escape) window.close();
}

void GottaCodeFast::onMouseButtonPressed(sf::Event event) {
}

