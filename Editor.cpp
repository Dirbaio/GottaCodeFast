#include "Editor.hpp"
#include "GottaCodeFast.hpp"

#define FONTSIZE 20

Editor::Line::Line(Editor* editor, std::string content) : editor(editor), content(content), text(content,editor->getFont(),FONTSIZE) {
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

Editor::Editor(GottaCodeFast* game) : cursorPos(0,0), game(game) {
	font.loadFromFile("data/Monospace.ttf");
	lines.push_back(Line(this,"#include <iostream>"));
	lines.push_back(Line(this,"#include <vector>"));
	lines.push_back(Line(this,"using namespace std;"));
	lines.push_back(Line(this,""));
	lines.push_back(Line(this,"int main() {"));
	lines.push_back(Line(this,"    return 42;"));
	lines.push_back(Line(this,"}"));
}

Editor::~Editor() {
}

void Editor::update(float deltaTime) {
	(void) deltaTime;
}

void Editor::draw(sf::Vector2f pos) {
	for(unsigned int i = 0; i < lines.size(); ++i)
		lines[i].draw(pos+sf::Vector2f(0,FONTSIZE*i));
	sf::RectangleShape r(sf::Vector2f(2,FONTSIZE));
	r.setFillColor(sf::Color::White);
	r.setPosition(pos + sf::Vector2f(cursorPos.x*12, cursorPos.y * FONTSIZE + 3));
	if(sin(GLOBALCLOCK.getElapsedTime().asSeconds()*5) < 0.5
	   || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
	   || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
	   || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
	   || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
	   || sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		game->getWindow().draw(r);
}

void Editor::saveToFile(std::string filePath) {
	std::ofstream file(filePath,std::ofstream::out|std::ofstream::trunc);
	for(unsigned int i = 0; i < lines.size(); ++i) file << lines[i].getContent() << '\n';
	file.close();
}

void Editor::forward() {
	if(isPositionValid(cursorPos + sf::Vector2i(1,0))) ++cursorPos.x;
}

void Editor::backward() {
	if(isPositionValid(cursorPos - sf::Vector2i(1,0))) --cursorPos.x;
}

void Editor::up() {
	if(cursorPos.y == 0) return;
	--cursorPos.y;
	if(!isPositionValid(cursorPos))
		cursorPos.x = lines[cursorPos.y].getContent().size();
}

void Editor::down() {
	if(cursorPos.y == int(lines.size())-1) return;
	++cursorPos.y;
	if(!isPositionValid(cursorPos))
		cursorPos.x = lines[cursorPos.y].getContent().size();
}

void Editor::del() {
	if(cursorPos.x == 0) {
		if(cursorPos.y == 0) return;
		std::vector<Line> newDocument;
		int last = lines[cursorPos.y-1].getContent().size();
		for(int i = 0; i < cursorPos.y-1; ++i) newDocument.push_back(lines[i]);
		newDocument.push_back(Line(this,lines[cursorPos.y-1].getContent()+lines[cursorPos.y].getContent()));
		for(unsigned int i = cursorPos.y+1; i < lines.size(); ++i) newDocument.push_back(lines[i]);
		lines = newDocument;
		--cursorPos.y;
		cursorPos.x = last;
		return;
	}
	lines[cursorPos.y].del(cursorPos.x-1);
	--cursorPos.x;
}

void Editor::insert(char c) {
	lines[cursorPos.y].add(cursorPos.x, c);
	++cursorPos.x;
}

void Editor::newline() {
	std::vector<Line> newDocument;
	for(int i = 0; i < cursorPos.y; ++i) newDocument.push_back(lines[i]);
	newDocument.push_back(Line(this, lines[cursorPos.y].getContent().substr(0,cursorPos.x)));
	newDocument.push_back(Line(this, lines[cursorPos.y].getContent().substr(cursorPos.x,lines[cursorPos.y].getContent().size())));
	for(unsigned int i = cursorPos.y+1; i < lines.size(); ++i) newDocument.push_back(lines[i]);
	cursorPos.x = 0;
	++cursorPos.y;
	lines = newDocument;
}

void Editor::process(sf::Event event) { //to broken, sfml SUCKEA MUCSO PARA ESTA MIERDA, SDL PLS
	std::string s = "";
	bool b = event.key.shift;
	switch (event.key.code) {
		case sf::Keyboard::A: s += b?"A":"a"; break;
		case sf::Keyboard::B: s += b?"B":"b"; break;
		case sf::Keyboard::C: s += b?"C":"c"; break;
		case sf::Keyboard::D: s += b?"D":"d"; break;
		case sf::Keyboard::E: s += b?"E":"e"; break;
		case sf::Keyboard::F: s += b?"F":"f"; break;
		case sf::Keyboard::G: s += b?"G":"g"; break;
		case sf::Keyboard::H: s += b?"H":"h"; break;
		case sf::Keyboard::I: s += b?"I":"i"; break;
		case sf::Keyboard::J: s += b?"J":"j"; break;
		case sf::Keyboard::K: s += b?"K":"k"; break;
		case sf::Keyboard::L: s += b?"L":"l"; break;
		case sf::Keyboard::M: s += b?"M":"m"; break;
		case sf::Keyboard::N: s += b?"N":"n"; break;
		case sf::Keyboard::O: s += b?"O":"o"; break;
		case sf::Keyboard::P: s += b?"P":"p"; break;
		case sf::Keyboard::Q: s += b?"Q":"q"; break;
		case sf::Keyboard::R: s += b?"R":"r"; break;
		case sf::Keyboard::S: s += b?"S":"s"; break;
		case sf::Keyboard::T: s += b?"T":"t"; break;
		case sf::Keyboard::U: s += b?"U":"u"; break;
		case sf::Keyboard::V: s += b?"V":"v"; break;
		case sf::Keyboard::W: s += b?"W":"w"; break;
		case sf::Keyboard::X: s += b?"X":"x"; break;
		case sf::Keyboard::Y: s += b?"Y":"y"; break;
		case sf::Keyboard::Z: s += b?"Z":"z"; break;
		case sf::Keyboard::Space: s += " "; break;
		case sf::Keyboard::BackSlash: s += "\\"; break;
		case sf::Keyboard::Slash: s += "/"; break;
		case sf::Keyboard::Dash: s += "-"; break;
		case sf::Keyboard::Quote: s += ""; break;
		case sf::Keyboard::Multiply: s += "*"; break;
		case sf::Keyboard::LBracket: s += "["; break;
		case sf::Keyboard::RBracket: s += "]"; break;
		case sf::Keyboard::Period: s += "."; break;
		case sf::Keyboard::SemiColon: s += ";"; break;
		case sf::Keyboard::Comma: s += ","; break;
		case sf::Keyboard::Tilde: s += ""; break;
		case sf::Keyboard::Tab: s += "    "; break;
		case sf::Keyboard::Unknown: s += "UnknownKey"; break;
		default: break;
	}
	for(unsigned int i = 0; i < s.size(); ++i) insert(s[i]);
}

bool Editor::isPositionValid(sf::Vector2i pos) {
	return !(pos.y < 0 || pos.y > int(lines.size()) || pos.x < 0 || pos.x > int(lines[pos.y].getContent().size()));
}
