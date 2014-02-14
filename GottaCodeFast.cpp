#include "GottaCodeFast.hpp"

GottaCodeFast::GottaCodeFast() {
	font.loadFromFile("data/Monospace.ttf");
	txt = sf::Text("HOLA", font, 100);
	txt.setPosition(sf::Vector2f(10,10));
	txt.setColor(sf::Color::White);
}

GottaCodeFast::~GottaCodeFast() {
}

void GottaCodeFast::update(float deltaTime) {
}

void GottaCodeFast::draw() {
	editor.draw(sf::Vector2f(100,100));
}

void GottaCodeFast::onKeyPressed(sf::Event event) {
}

void GottaCodeFast::onMouseButtonPressed(sf::Event event) {
}

