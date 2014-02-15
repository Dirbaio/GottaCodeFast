#ifndef EDITOR_HPP
#define EDITOR_HPP
#include "tools.hpp"

class GottaCodeFast;
class Editor {
		class Line {
			public:
				Line(Editor* editor);
				~Line();

				void add(int pos, char c);
				void del(int pos);

				void draw(sf::Vector2f pos);

				std::string getContent();
			private:
				Editor* editor;
				std::string content;
				sf::Text text;
		};

	public:
		Editor(GottaCodeFast* game);
		~Editor();

		void update(float deltaTime);
		void draw();
		void saveToFile(std::string filePath);

		const sf::Font& getFont() {return font;}
		GottaCodeFast* getGame() {return game;}

	private:
		GottaCodeFast* game;
		sf::Font font;
		std::vector<Line> lines;
};

#endif // EDITOR_HPP
