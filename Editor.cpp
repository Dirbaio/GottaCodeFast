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

Editor::Editor(GottaCodeFast* game) : cursorPos(0,0), game(game), cursorTime(0) {
	font.loadFromFile("data/Monospace.ttf");
	lines.push_back(Line(this,"#include <iostream>"));
	lines.push_back(Line(this,"#include <vector>"));
	lines.push_back(Line(this,"using namespace std;"));
	lines.push_back(Line(this,""));
	lines.push_back(Line(this,"int main() {"));
	lines.push_back(Line(this,"\treturn 42;"));
	lines.push_back(Line(this,"}"));
}

Editor::~Editor() {
}

void Editor::update(float deltaTime) {
	(void) deltaTime;
	cursorTime += deltaTime;
}

void Editor::draw(sf::Vector2f pos) {
	for(unsigned int i = 0; i < lines.size(); ++i)
		lines[i].draw(pos+sf::Vector2f(0,FONTSIZE*i));
	sf::RectangleShape r(sf::Vector2f(2,FONTSIZE));
	r.setFillColor(sf::Color::White);
	r.setPosition(pos + sf::Vector2f(cursorPos.x*12-1, cursorPos.y * FONTSIZE + 3));
	if(cursorTime - int(cursorTime) < 0.5)
		game->getWindow().draw(r);
}

void Editor::saveToFile(std::string filePath) {
	std::ofstream file(filePath,std::ofstream::out|std::ofstream::trunc);
	for(unsigned int i = 0; i < lines.size(); ++i) file << lines[i].getContent() << '\n';
	file.close();
}

void Editor::forward() {
	if(cursorPos.x == int(lines[cursorPos.y].getContent().size()) && cursorPos.y + 1 < lines.size())
	{
		cursorPos.y++;
		cursorPos.x = -1;
	}
	if(isPositionValid(cursorPos + sf::Vector2i(1,0))) ++cursorPos.x;
}

void Editor::backward() {
	if(cursorPos.x == 0 && cursorPos.y != 0)
	{
		cursorPos.y--;
		cursorPos.x = int(lines[cursorPos.y].getContent().size());
	}
	else
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


void Editor::process(int key) {
	cursorTime = 0;

	switch(key)
	{
		case 1: forward(); break;
		case 2: backward(); break;
		case 3: up(); break;
		case 4: down(); break;
		case 8: del(); break;
		case 13: newline(); break;
		case 9: insert('\t'); break;
		case 127:
		{
			sf::Vector2i v = cursorPos;
			forward();
			if(cursorPos != v)
				del();
			break;
		}
		default:
			insert(char(key));
			break;
	}
}

bool Editor::isPositionValid(sf::Vector2i pos) {
	if(pos.y < 0) return false;
	if(pos.y >= int(lines.size())) return false;
	if(pos.x < 0) return false;
	if(pos.x > int(lines[pos.y].getContent().size())) return false;
	return true;
}
