#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>

class GottaCodeFast;
class Interface {
	private:
		GottaCodeFast* game;
		sf::Sprite background;
		sf::Sprite tiempo;
		float tTotal,tParcial;
		sf::Text problem;
	public:
		Interface(GottaCodeFast* game);
		void draw();
		void update(float deltaTime);
		bool timeUp() const { return (tParcial == 0); }
		void resetTime(float t);
		void setStatement(std::string s);
	private:
		sf::RectangleShape timerBack;
		sf::RectangleShape timerFront;

};

#endif // INTERFACE_HPP
