#ifndef MONSTER_H
#define MONSTER_H
 #include <SFML/Graphics.hpp>

class Monster : public sf::Sprite
{
	protected:
		sf::Texture texture;
		float speed;
		sf::Vector2f posFinal;
	public:
		Monster();
		virtual void loadTexture() = 0;
		virtual void update(float deltaTime) = 0;
		void setPosFinal(sf::Vector2f d);
};

#endif // MONSTER_H
