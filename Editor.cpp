#include "Editor.hpp"
#include "GottaCodeFast.hpp"
#include "Resources.hpp"

#define FONTSIZE 20

std::string Editor::Line::keywords[KEYWORDS_SIZE] {
	"return",
	"int",
	"float",
	"char",
	"short",
	"double",
	"using",
	"namespace",
	"class",
	"struct",
	"template",
	"typename",
	"static",
	"public",
	"private",
	"protected",
	"const",
	"switch",
	"break",
	"case",
	"#define",
	"typedef",
	"#include",
	"#ifndef",
	"#ifdef",
	"#else",
	"if",
	"else",
	"for",
	"while",
	"do",
	"virtual",
	"unsigned",
	"mutable",
	"auto",
	"sizeof",
	"bool",
	"nullptr",
	"operator",
	"volatile",
	"delete",
	"dynamic_cast",
	"static_cast",
	"const_cast",
	"default",
	"continue",
	"this",
	"long",
	"false",
	"true",
	"enum",
	"void"
};

Editor::Line::Line(Editor* editor, std::string content) : editor(editor), content(content), text("", Resources::font,FONTSIZE) {
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

bool Editor::Line::startsKeyword(int pos, int keyword) {
	std::string key = keywords[keyword];
	bool same = true;
	for(unsigned int i = 0; i < key.size() && same; ++i)
		if(content[pos+i] != key[i]) same = false;
	if(!same) return false;
	if(pos+key.size()-1 >= content.size()) return false;
	//left limit
	if(pos != 0) {
		char c = content[pos-1];
		if((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || c == '_') return false;
	}
	//right limit
	if(pos+key.size()-1 != content.size()-1) {
		char c = content[pos+key.size()];
		if((c <= 'Z' && c >= 'A') || (c <= 'z' && c >= 'a') || c == '_') return false;
	}
	return true;
}

void Editor::Line::draw(sf::Vector2f pos) {
	unsigned int index = 0;
	while(index < content.size()) {
		for(int k = 0; k < KEYWORDS_SIZE; ++k) {
			if(!startsKeyword(index,k)) continue;
			for(unsigned int i = 0; i < keywords[k].size(); ++i) {
				text.setColor(sf::Color::Cyan);
				text.setStyle(sf::Text::Bold);
				text.setPosition(pos+sf::Vector2f(posToX(index)*12,0));
				text.setString(content[index]);
				std::cout << content[index] << std::endl;
				editor->getGame()->getWindow().draw(text);
				++index;
			}
		}
		if(index < content.size()) {
			text.setColor(sf::Color::White);
			text.setStyle(sf::Text::Regular);
			text.setPosition(pos+sf::Vector2f(posToX(index)*12,0));
			text.setString(content[index]);
			editor->getGame()->getWindow().draw(text);
			++index;
		}
	}
}

int Editor::Line::xToPos(int x) {
	for(unsigned int i = 0; i < content.size(); i++) {
		if(x <= 0)
			return i;
		if(content[i] == '\t')
			x -= 4;
		else
			x--;
	}

	return content.size();
}

int Editor::Line::posToX(int pos) {
	int px = 0;
	for(int i = 0; i < pos && i < int(content.size()); i++)
		if(content[i] == '\t')
			px += 4;
		else
			px++;

	return px;
}

std::string Editor::Line::getIndent() const {
	std::string r;
	for(unsigned int i = 0; i < content.size(); i++)
		if(content[i] == '\t' || content[i] == ' ')
			r += content[i];
		else
			break;
	return r;
}

Editor::Editor(GottaCodeFast* game) : hasSavePos(false), cursorTime(0), cursorPos(0,0), game(game) {
}

Editor::~Editor() {
}

void Editor::update(float deltaTime) {
	(void) deltaTime;
	cursorTime += deltaTime;
}

void Editor::draw(sf::Vector2f pos) {
	std::cout << "DRAW" << std::endl;
	for(unsigned int i = 0; i < lines.size(); ++i)
		lines[i].draw(pos+sf::Vector2f(0,FONTSIZE*i));
	sf::RectangleShape r(sf::Vector2f(2,FONTSIZE));
	r.setFillColor(sf::Color::White);
	std::string str = lines[cursorPos.y].getContent();
	r.setPosition(pos + sf::Vector2f(lines[cursorPos.y].posToX(cursorPos.x)*12-1, cursorPos.y * FONTSIZE + 3));
	if(cursorTime - int(cursorTime) < 0.5)
		game->getWindow().draw(r);
}

void Editor::saveToFile(std::string filePath) {
	std::ofstream file(filePath,std::ofstream::out|std::ofstream::trunc);
	for(unsigned int i = 0; i < lines.size(); ++i) file << lines[i].getContent() << '\n';
	file.close();
}

void Editor::forward() {
	if(cursorPos.x == int(lines[cursorPos.y].getContent().size()) && cursorPos.y + 1 < int(lines.size())) {
		cursorPos.y++;
		cursorPos.x = -1;
	}
	if(isPositionValid(cursorPos + sf::Vector2i(1,0))) ++cursorPos.x;
}

void Editor::backward() {
	if(cursorPos.x == 0 && cursorPos.y != 0) {
		cursorPos.y--;
		cursorPos.x = int(lines[cursorPos.y].getContent().size());
	}
	else
		if(isPositionValid(cursorPos - sf::Vector2i(1,0))) --cursorPos.x;
}

void Editor::up() {
	if(cursorPos.y == 0) return;
	if(!hasSavePos)
		savePos = lines[cursorPos.y].posToX(cursorPos.x);
	hasSavePos = true;
	--cursorPos.y;
	cursorPos.x = lines[cursorPos.y].xToPos(savePos);
}

void Editor::down() {
	if(cursorPos.y == int(lines.size())-1) return;
	if(!hasSavePos)
		savePos = lines[cursorPos.y].posToX(cursorPos.x);
	hasSavePos = true;
	++cursorPos.y;
	cursorPos.x = lines[cursorPos.y].xToPos(savePos);
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
	std::string ind = lines[cursorPos.y].getIndent();
	newDocument.push_back(Line(this, ind + lines[cursorPos.y].getContent().substr(cursorPos.x,lines[cursorPos.y].getContent().size())));
	for(unsigned int i = cursorPos.y+1; i < lines.size(); ++i) newDocument.push_back(lines[i]);
	cursorPos.x = ind.size();
	++cursorPos.y;
	lines = newDocument;
}

void Editor::setProgram(std::string p) {
	std::stringstream ss(p);
	std::string item;
	int y = 0;
	while (std::getline(ss, item)) {
		for(int i = 0; i < item.size(); i++)
			if(item[i] == '$')
			{
				item.erase(item.begin()+i);
				cursorPos.y = y;
				cursorPos.x = i;
				break;
			}
		y++;
		lines.push_back(Line(this, item));
	}
}

void Editor::process(int key) {
	cursorTime = 0;

	if(key != 3 && key != 4)
		hasSavePos = false;

	switch(key) {
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
