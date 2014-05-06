#include "Player.hpp"
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>
#include "Resources.hpp"

Player::Player(int num, GottaCodeFast& game) : game(game), playerNum(num), editor(&game), kbd(std::string("keyboard")+char('1'+playerNum))
{
    messageTime = -1;
    editor.setProgram(game.prob.start);
    compiling = false;
}

void Player::update(float deltaTime) {

    kbd.update();
    while(!kbd.events.empty())
    {
        int k = kbd.events.front();
        kbd.events.pop();

        if(k == ESC)
            exit(1);
        else if(k == F5)
            compile();
        else
            editor.process(k);
    }

    int t2 = int(game.time);
    if(t1 != t2)
    {
        if(t1 == 0) setMessage("3", 1, sf::Color(50, 255, 20));
        if(t1 == 1) setMessage("2", 1, sf::Color(50, 255, 20));
        if(t1 == 2) setMessage("1", 1, sf::Color(50, 255, 20));
        if(t1 == 3)
        {
            setMessage("Go!", 1, sf::Color(50, 255, 20));
            //ui.resetTime(timeLimit);
        }
    }

    editor.update(deltaTime);

    //Update compiler
    if(compiling) {
        int status;
        int ret = waitpid(pid, &status, WNOHANG);
        if(ret == -1) {
            std::cout<<"Error with waitpid"<<std::endl;
            exit(1);
        }
        if(ret != 0) {
            //El proceso ha acabado
            compiling = false;

            std::string errors = "";

            char buf[256];
            while((ret = read(errorfd, buf, sizeof(buf))) > 0) {
                std::string s(buf, ret);
                errors += s;
            }
            close(errorfd);

            compilationFinished(WEXITSTATUS(status), errors);
        }
    }

    messageTime -= deltaTime;
}

void Player::draw() {

    int xPos = 35 + playerNum*1000;
    editor.draw(sf::Vector2f(xPos, 95));

    if(messageTime > 0)
    {
        sf::Text msg = sf::Text(message, Resources::messageFont, 100);
        msg.setColor(messageColor);
        sf::FloatRect textRect = msg.getLocalBounds();
        sf::Vector2u s = game.getWindow().getSize();
        msg.setOrigin(textRect.left + textRect.width/2.0f,
                             textRect.top  + textRect.height/2.0f);
        msg.setPosition(sf::Vector2f((s.x*(1+playerNum*2))/4.0f,s.y/2.0f));
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
        game.getWindow().draw(msg);
    }
}


void Player::compilationFinished(int status, std::string errors)
{
    (void)errors;

    float len = 1.5;
    switch(status)
    {
        case 0:	setMessage("Bien!", len, sf::Color(50, 255, 20)); break;
        case 1:	setMessage("WTF?!", len, sf::Color(255, 0, 0)); break;
        case 2:	setMessage("No compila!", len, sf::Color(255, 150, 0)); break;
        case 3:	setMessage("Esta mal!", len, sf::Color(255, 0, 150)); break;
        case 4:	setMessage("CRASH!", len, sf::Color(255, 0, 0)); break;
        case 5:	setMessage("El programa no acaba...", len, sf::Color(0, 120, 255)); break;
    }

    if(status == 0)
    {
//        done = true;
//        doneTime = 2;
    }
}


void Player::compile() {
    if(compiling) {
        std::cout<<"Already compiling!"<<std::endl;
        return;
    }

    compiling = true;

    int p[2];
    pipe2(p, 0); //O_NONBLOCK);

    editor.saveToFile(std::string("data/judge/tmp/program")+char('1'+playerNum)+".cpp");
    pid = fork();
    if(pid == -1) {
        std::cout<<"fork fail"<<std::endl;
        exit(1);
    }

    if(pid == 0) {
        close(p[0]);
        dup2(p[1], 2);
        close(p[1]);
        std::string bla = std::string("program")+char('1'+playerNum);
        execlp("/bin/bash", "/bin/bash", "data/judge/judge.sh", game.prob.name.c_str(), bla.c_str(), NULL);
        std::cout<<"EXECLP FAIL"<<std::endl;
        exit(1);
    }

    setMessage("Ejecutando...", 100, sf::Color(255, 255, 255, 128));
    close(p[1]);
    errorfd = p[0];
}


void Player::setMessage(std::string msg, float time, sf::Color messageColor) {
    this->message = msg;
    this->messageTime = time;
    this->messageTimeStart = time;
    this->messageColor = messageColor;
}
