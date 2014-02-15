#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>

class GottaCodeFast;
class Interface {
	private:
		GottaCodeFast* game;
		sf::Sprite background;
		sf::Texture fondo;
	public:
		Interface(GottaCodeFast* game);
		void init();
		void draw();
		void update(float deltaTime);
};

#endif // INTERFACE_HPP
