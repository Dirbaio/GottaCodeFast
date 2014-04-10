#ifndef TOOLS_HPP
#define TOOLS_HPP

//SFML (Simple Fast Media Library)
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//STL (Standard Toolkit Library)
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <list>
#include <cstring>
#include <queue>
#include <limits>

#define ASSERT(expression, string) do \
{ \
	if(!(expression)) { \
		std::cout << "ASSERT FAILED, STOPPING " << std::endl;\
		std::cout << "Reason: " << string << std::endl; \
		std::cout << "At file " << __FILE__ \
		<< " inside function " << __PRETTY_FUNCTION__ << " on line " << __LINE__ << std::endl; \
		assert(expression); \
		std::exit(-1); \
	} \
} while (0)

extern const sf::Clock GLOBALCLOCK;

enum {
    RIGHT_KEY,
    LEFT_KEY,
    UP_KEY,
    DOWN_KEY,
    HOME_KEY,
    END_KEY,
    CONTROL_KEY,
    SHIFT_KEY,
    DELETE_KEY,
    RETURN_KEY,
    TAB_KEY,
    F5_KEY,
    ESC_KEY
};


#endif // TOOLS_HPP
