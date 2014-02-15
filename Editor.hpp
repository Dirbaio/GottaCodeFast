#ifndef EDITOR_HPP
#define EDITOR_HPP
#include "tools.hpp"

class GottaCodeFast;
class Editor {
	private:
		class Line {
			public:
				Line(Editor* editor, std::string content = "");
				~Line();

				void add(int pos, char c);
				void del(int pos);

				void draw(sf::Vector2f pos);

				std::string getContent() const {return content;}
			private:
				Editor* editor;
				std::string content;
				sf::Text text;
		};

	public:
		Editor(GottaCodeFast* game);
		~Editor();

		//main
		void update(float deltaTime);
		void draw(sf::Vector2f pos);
		void saveToFile(std::string filePath);

		//gets
		const sf::Font& getFont() const {return font;}
		GottaCodeFast* getGame() const {return game;}

		//actions
		void forward();
		void backward();
		void up();
		void down();
		void del();
		void insert(char c);
		void newline();

		void process(int key);

	private:
		bool isPositionValid(sf::Vector2i pos);

		float cursorTime;
		sf::Vector2i cursorPos;
		GottaCodeFast* game;
		sf::Font font;
		std::vector<Line> lines;
};

#endif // EDITOR_HPP
