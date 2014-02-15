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
		sf::Text problem;
	public:
		Interface(GottaCodeFast* game);
		void draw();
		void update(float deltaTime);
		bool timeUp() const { return (tParcial == 0); }
		void resetTime(float t);
		void setMessage(std::string msg, float time, sf::Color messageColor = sf::Color(255, 255, 255));
		void setStatement(std::string s);
	private:
		sf::RectangleShape timerBack;
		sf::RectangleShape timerFront;

		sf::Color messageColor;
		std::string message;
		float messageTime;
		float messageTimeStart;
};

#endif // INTERFACE_HPP
