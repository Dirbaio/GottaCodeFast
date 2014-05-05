#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include<string>

class Keyboard
{
	public:
		Keyboard(std::string device);
		~Keyboard();
		void update();

	private:

		void keyUp(int code);
		void keyDown(int code);
		int codeToChar(int code);

		int fd;
		bool shift;
		bool alt;

};

#endif // KEYBOARD_HPP
