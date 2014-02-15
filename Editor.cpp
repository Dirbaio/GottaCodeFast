#include "Editor.hpp"
#include "GottaCodeFast.hpp"

Editor::Line::Line(Editor* editor) : editor(editor), content(""), text("",editor->getFont(),100) {
}

Editor::Line::~Line() {
}

void Editor::Line::add(int pos, char c) {
	std::string str = std::string("") + c;
	content.insert(pos,str);
}

void Editor::Line::del(int pos) {
	content.erase(pos,1);
}

void Editor::Line::draw(sf::Vector2f pos) {
	text.setColor(sf::Color::White);
	text.setPosition(pos);
	text.setString(content);
	editor->getGame()->getWindow().draw(text);
}

std::string Editor::Line::getContent() {
}

Editor::Editor(GottaCodeFast* game) : game(game) {
}

Editor::~Editor() {
}

void Editor::update(float deltaTime) {
}

void Editor::draw() {
}

void Editor::saveToFile(std::string filePath) {
	std::ofstream file(filePath,std::ofstream::out|std::ofstream::trunc);
	for(unsigned int i = 0; i < lines.size(); ++i) file << lines[i].getContent() << '\n';
	file.close();
}
