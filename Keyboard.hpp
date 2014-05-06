#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include<string>
#include<queue>


const char RIGHT = 1;
const char LEFT = 2;
const char UP = 3;
const char DOWN = 4;
const char F5 = 5;
const char HOME = 6;
const char END = 7;
const char ESC = 8;
const char PAGEUP = 11;
const char PAGEDOWN = 12;
const char BACKSPACE = 13;
const char DEL = 14;

class Keyboard
{
	public:
		Keyboard(std::string device);
		~Keyboard();
		void update();

        std::queue<int> events;
	private:

		void keyUp(int code);
		void keyDown(int code);
		int codeToChar(int code);

		int fd;
		bool shift;
		bool alt;


};

#endif // KEYBOARD_HPP
