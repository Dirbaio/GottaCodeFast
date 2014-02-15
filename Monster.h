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
		virtual void loadTexture() = 0;
		virtual void update(float deltaTime) = 0;
		void setPosFinal(sf::Vector2f d);
};

#endif // MONSTER_H
