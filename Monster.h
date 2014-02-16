#ifndef MONSTER_H
#define MONSTER_H
 #include <SFML/Graphics.hpp>

class Monster : public sf::Sprite
{
	protected:
		float speed;
		sf::Vector2f posFinal;
		bool alive,waiting;
	public:
		Monster();
		virtual void update(float deltaTime) = 0;
		virtual bool isClicked(sf::Vector2f pos) = 0;
		void setPosFinal(sf::Vector2f d);
		bool isWaiting();
		bool isAlive();
		virtual void die() = 0;
};

#endif // MONSTER_H
