#include "Monster.h"

Monster::Monster(){}

void Monster::setPosFinal(sf::Vector2f d){
	posFinal = d;
}

bool Monster::isWaiting(){
	return waiting;
}

bool Monster::isAlive(){
	return alive;
}
