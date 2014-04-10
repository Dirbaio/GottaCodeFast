#ifndef EDITOR_HPP
#define EDITOR_HPP
#include "tools.hpp"

#define KEYWORDS_SIZE 52

class GottaCodeFast;
class Editor {
	private:
		class Line {
				static std::string keywords[KEYWORDS_SIZE];

			public:
				Line(Editor* editor, std::string content = "");
				~Line();

				void add(int pos, char c);
				void del(int pos);
				int xToPos(int x);
				int posToX(int pos);
                int getYPosition();
				void draw(sf::Vector2f pos);

				std::string getContent() const {return content;}
				std::string getIndent() const;
			private:
				int startsNumber(int pos);
				bool startsKeyword(int pos, int keyword);
				int findEnclosing(int pos, char enc);

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
        void home();
        void end();
		void del();
		void insert(char c);
		void newline();

		void process(int key);

        void setCtrlKey(bool pressed);
        void setShiftKey(bool pressed);

		void setProgram(std::string p);

		sf::Vector2u getRandomCharPos();
	private:
		bool isPositionValid(sf::Vector2i pos);

		int savePos;
		bool hasSavePos;

        bool ctrlPressed;
        bool shiftPressed;

		float cursorTime;
		sf::Vector2i cursorPos;
		GottaCodeFast* game;
		sf::Font font;
		std::vector<Line> lines;
};

#endif // EDITOR_HPP
