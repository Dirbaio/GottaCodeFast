#include "Keyboard.hpp"
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


Keyboard::Keyboard(std::string device)
{
	fd = 0;
	fd = open(device.c_str(), O_RDONLY | O_NONBLOCK);
	if(fd == -1)
	{
		printf("Opening keyboard device: %s\n", device.c_str());
		perror("Can't open keyboard device");
		exit(1);
	}

	shift = false;
	alt = false;
}

Keyboard::~Keyboard()
{
	if(fd > 9)
		close(fd);
}

void Keyboard::update()
{
	struct input_event e;

	while(read(fd, &e, sizeof(struct input_event)) == sizeof(struct input_event))
	{
		if(e.type == 1 && e.value == 1) keyDown(e.code);
		if(e.type == 1 && e.value == 2) keyDown(e.code); //Key repeated
		if(e.type == 1 && e.value == 0) keyUp(e.code);
	}
}


int Keyboard::codeToChar(int code)
{
	switch(code) {
		case 1: 	return ESC;
		case 2: 	return alt ? '|' : shift ? '!' : '1';
		case 3: 	return alt ? '@' : shift ? '"' : '2';
		case 4: 	return alt ? '#' : shift ? L'·' : '3';
		case 5: 	return alt ? '~' : shift ? '$' : '4';
		case 6: 	return alt ? L'½' : shift ? '%' : '5';
		case 7: 	return alt ? L'¬' : shift ? '&' : '6';
		case 8: 	return alt ? '{' : shift ? '/' : '7';
		case 9: 	return alt ? '[' : shift ? '(' : '8';
		case 10: 	return alt ? ']' : shift ? ')' : '9';
		case 11: 	return alt ? '}' : shift ? '=' : '0';
		case 12:	return alt ? '\\' : shift ? '?' : '\'';
		case 13:	return alt ? '~' : shift ? L'¿' : L'¡';
		case 14:	return BACKSPACE;
		case 15:	return '\t';
		case 16:	return shift ? 'Q' : 'q';
		case 17:	return shift ? 'W' : 'w';
		case 18:	return shift ? 'E' : 'e';
		case 19:	return shift ? 'R' : 'r';
		case 20:	return shift ? 'T' : 't';
		case 21:	return shift ? 'Y' : 'y';
		case 22:	return shift ? 'U' : 'u';
		case 23:	return shift ? 'I' : 'i';
		case 24:	return shift ? 'O' : 'o';
		case 25:	return shift ? 'P' : 'p';
		case 26:	return alt ? '[' : shift ? '^' : '`';
		case 27:	return alt ? ']' : shift ? '*' : '+';
		case 28:	return '\n';
		case 30:	return shift ? 'A' : 'a';
		case 31:	return shift ? 'S' : 's';
		case 32:	return shift ? 'D' : 'd';
		case 33:	return shift ? 'F' : 'f';
		case 34:	return shift ? 'G' : 'g';
		case 35:	return shift ? 'H' : 'h';
		case 36:	return shift ? 'J' : 'j';
		case 37:	return shift ? 'K' : 'k';
		case 38:	return shift ? 'L' : 'l';
		case 39:	return shift ? L'Ñ' : L'ñ';
		case 40:	return alt ? '{' : shift ? '"' : L'´';
		case 41:	return alt ? '\\' : shift ? L'ª' : L'º';
		case 43:	return alt ? '}' : shift ? L'Ç' : L'ç';
		case 86:	return shift ? '>' : '<';
		case 44:	return shift ? 'Z' : 'z';
		case 45:	return shift ? 'X' : 'x';
		case 46:	return shift ? 'C' : 'c';
		case 47:	return shift ? 'V' : 'v';
		case 48:	return shift ? 'B' : 'b';
		case 49:	return shift ? 'N' : 'n';
		case 50:	return shift ? 'M' : 'm';
		case 51:	return shift ? ';' : ',';
		case 52:	return shift ? ':' : '.';
		case 53:	return shift ? '_' : '-';
        case 57:    return ' ';
		case 102:	return HOME;
		case 107:	return END;
		case 111: 	return DEL;
		case 104:	return PAGEUP;
		case 109:	return PAGEDOWN;
		case 106:	return RIGHT;
		case 105:	return LEFT;
		case 103: 	return UP;
		case 108:	return DOWN;
        case 63:    return F5;
	}

	return 0;
}

void Keyboard::keyDown(int code)
{
	if(code == 42) { shift = true; return; }
	if(code == 54) { shift = true; return; }
	if(code == 100) { alt = true; return; }

	int c = codeToChar(code);
	if(c)
        events.push(c);
}

void Keyboard::keyUp(int code)
{
	if(code == 42) { shift = false; return; }
	if(code == 54) { shift = false; return; }
	if(code == 100) { alt = false; return; }

}
