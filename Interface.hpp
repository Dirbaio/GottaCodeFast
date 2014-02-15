#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>

class GottaCodeFast;
class Interface {
	private:
		GottaCodeFast* game;
		sf::Texture fondo;
		sf::Sprite background;
		sf::Sprite tiempo;
		float tTotal,tParcial;
		sf::Font fuente;
		sf::Text puntuacion;
	public:
		Interface(GottaCodeFast* game);
		void init();
		void draw();
		void update(float deltaTime);
};

#endif // INTERFACE_HPP
