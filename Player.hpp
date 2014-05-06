#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GottaCodeFast.hpp"

class Player
{
public:
    Player(int num, GottaCodeFast& game);

    void update(float deltaTime);
    void draw();
    void compile();
    void compilationFinished(int status, std::string errors);
    void onKeyPressed(int key);


    GottaCodeFast& game;
    int playerNum;
    Editor editor;
    Keyboard kbd;
    bool compiling;
    int pid;
    int errorfd;
    std::string output;

    int t1;

    void setMessage(std::string msg, float time, sf::Color messageColor = sf::Color(255, 255, 255));
    sf::Color messageColor;
    std::string message;
    float messageTime;
    float messageTimeStart;

};

#endif // PLAYER_HPP
