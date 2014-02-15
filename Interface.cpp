#include "Interface.hpp"
#include "GottaCodeFast.hpp"
#include "Resources.hpp"

Interface::Interface(GottaCodeFast* game) : game(game) {
	//BACKGROUND
	fondo.loadFromFile("data/background.jpg");
	background.setTexture(fondo);
	sf::Vector2u s = game->getWindow().getSize();
	float scaleX = float(s.x)/fondo.getSize().x;
	float scaleY = float(s.y)/fondo.getSize().y;
	background.setScale(scaleX,scaleY);
	background.setPosition(sf::Vector2f(0,0));
	//TIMER BAR
	timerBack = sf::RectangleShape(sf::Vector2f(100,800));
	timerBack.setPosition(100,100);
	timerBack.setFillColor(sf::Color(50,50,50));
	timerFront = sf::RectangleShape(sf::Vector2f(90,-790));
	timerFront.setPosition(105,895);
	timerFront.setFillColor(sf::Color(200,200,200));

	problem = sf::Text("", Resources::messageFont, 30);
	sf::FloatRect textRect = problem.getLocalBounds();
	problem.setPosition(sf::Vector2f(250.0f,40.0f));
	messageTime = -1;
}

void Interface::setStatement(std::string s)
{
	problem.setString(s);
}

void Interface::draw() {
	//game->getWindow().draw(background);
	game->getWindow().draw(problem);
	game->getWindow().draw(tiempo);
	game->getWindow().draw(timerBack);
	game->getWindow().draw(timerFront);

	if(messageTime > 0)
	{
		sf::Text msg = sf::Text(message, Resources::messageFont, 100);
		msg.setColor(messageColor);
		sf::FloatRect textRect = msg.getLocalBounds();
		sf::Vector2u s = game->getWindow().getSize();
		msg.setOrigin(textRect.left + textRect.width/2.0f,
							 textRect.top  + textRect.height/2.0f);
		msg.setPosition(sf::Vector2f(s.x/2.0f,s.y/2.0f));
		float t = messageTimeStart-messageTime;

		float ang = sin(GLOBALCLOCK.getElapsedTime().asSeconds()*2)*10;
		float sc = 1;
		if(t < 0.2)
		{
			sc = 1+(0.2-t)*10;
			ang -= (0.2-t)*600;
		}
		msg.setRotation(ang);

		if(messageTime < 0.2)
			sc = messageTime / 0.2;
		msg.setScale(sc, sc);
		game->getWindow().draw(msg);
	}
}

void Interface::update(float deltaTime) {
	tParcial = std::fmax(tParcial-deltaTime,0);
	float porcentaje = tParcial/tTotal;
	timerFront.setSize(sf::Vector2f(timerFront.getSize().x,porcentaje*-790.0f));
	messageTime -= deltaTime;
}

void Interface::setMessage(std::string msg, float time, sf::Color messageColor) {
	this->message = msg;
	this->messageTime = time;
	this->messageTimeStart = time;
	this->messageColor = messageColor;
}

void Interface::resetTime(float t) {
	tTotal = t;
	tParcial = t;
}
