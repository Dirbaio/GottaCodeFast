#include "GottaCodeFast.hpp"
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

std::string readAll(std::string file)
{
	std::ifstream in(file);
	std::string s, res;
	while(getline(in, s))
		res += s + "\n";
	in.close();
	return res;
}

GottaCodeFast::GottaCodeFast(std::string problem, int scrwidth, int scrheight, std::string title, int style) : Game(scrwidth, scrheight, title, style), editor(this), ui(this), compiling(false) {
	this->problem = problem;
	time = 0;

	ui.setStatement(readAll("data/judge/"+problem+"/problem.txt"));
	editor.setProgram(readAll("data/judge/"+problem+"/start.cpp"));
	std::ifstream in("data/judge/"+problem+"/settings.txt");
	in>>timeLimit;
	in.close();

	timeUp = false;
	time = 0.9;
	done = false;
	doneTime = 10;
}

GottaCodeFast::~GottaCodeFast() {
}

void GottaCodeFast::addRandomWorm() {
//    Worm* w = new Worm();
//    sf::Vector2u editorPos = editor.getRandomCharPos();
//    w->setPosFinal(sf::Vector2f(editorPos.x, editorPos.y));
//    w->setPosition(sf::Vector2f(std::rand() % 2 == 0 ? 0.0f : window.getSize().x,editorPos.y));
//    monsters.push_back(w);
//    monstersObjective.push_back();
}

void GottaCodeFast::update(float deltaTime) {
	int t1 = int(time);
	time += deltaTime;
	int t2 = int(time);
	if(t1 != t2)
	{
		if(t1 == 0) ui.setMessage("3", 1, sf::Color(50, 255, 20));
		if(t1 == 1) ui.setMessage("2", 1, sf::Color(50, 255, 20));
		if(t1 == 2) ui.setMessage("1", 1, sf::Color(50, 255, 20));
		if(t1 == 3)
		{
			ui.setMessage("Go!", 1, sf::Color(50, 255, 20));
			ui.resetTime(timeLimit);
		}
	}

	editor.update(deltaTime);
	ui.update(deltaTime);

//    for(unsigned int i = 0; i < monsters.size(); ++i) {
//        Monster* m = monsters[i];
//        m->update(deltaTime);
//        if(m->isWaiting()) {

//        }
//    }

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

	if(ui.timeUp() && !timeUp && !done && time > 4.01)
	{
		timeUp = true;
		ui.setMessage("Tiempo!", 2, sf::Color(255, 200, 0));
		doneTime = 2;
	}

	if(doneTime < 9)
	{
		doneTime -= deltaTime;
		if(doneTime < 0)
			window.close();
	}
}

void GottaCodeFast::draw() {
	ui.draw();
	editor.draw(sf::Vector2f(250, 95));
	for(unsigned int i = 0; i < monsters.size(); ++i) window.draw(*monsters[i]);
}

void GottaCodeFast::onMouseButtonPressed(sf::Event event) {
    //addRandomWorm();
	//for(unsigned int i = 0; i < monsters.size(); ++i) monsters[i]->isClicked(sf::Vector2f(event.mouseButton.x,event.mouseButton.y));
}

void GottaCodeFast::compilationFinished(int status, std::string errors)
{
	float len = 1.5;
	switch(status)
	{
		case 0:	ui.setMessage("Bien!", len, sf::Color(50, 255, 20)); break;
		case 1:	ui.setMessage("WTF?!", len, sf::Color(255, 0, 0)); break;
		case 2:	ui.setMessage("No compila!", len, sf::Color(255, 150, 0)); break;
		case 3:	ui.setMessage("Esta mal!", len, sf::Color(255, 0, 150)); break;
		case 4:	ui.setMessage("CRASH!", len, sf::Color(255, 0, 0)); break;
		case 5:	ui.setMessage("El programa no acaba...", len, sf::Color(0, 120, 255)); break;
	}

	if(status == 0)
	{
		done = true;
		doneTime = 2;
	}
}

void GottaCodeFast::compile() {
	if(compiling) {
		std::cout<<"Already compiling!"<<std::endl;
		return;
	}

	compiling = true;

	int p[2];
	pipe2(p, 0); //O_NONBLOCK);

	editor.saveToFile("data/judge/program.cpp");
	pid = fork();
	if(pid == -1) {
		std::cout<<"fork fail"<<std::endl;
		exit(1);
	}

	if(pid == 0) {
		close(p[0]);
		dup2(p[1], 2);
		close(p[1]);
		execlp("/bin/bash", "/bin/bash", "data/judge/judge.sh", problem.c_str(), NULL);
		std::cout<<"EXECLP FAIL"<<std::endl;
		exit(1);
	}

	ui.setMessage("Ejecutando...", 100, sf::Color(255, 255, 255, 128));
	close(p[1]);
	errorfd = p[0];
}

void GottaCodeFast::onKeyPressed(int key) {
	if(key == 27)
	{
		window.close();
		exit(0);
	}

	else if(!timeUp && time > 4 && !done)
	{
        if(key == F5_KEY)
			compile();
        else if (key == CONTROL_KEY)
            editor.setCtrlKey(true);
        else if (key == SHIFT_KEY)
            editor.setShiftKey(true);
		else
			editor.process(key);
    }
}

void GottaCodeFast::onKeyReleased(int key) {
    switch(key) {
    case CONTROL_KEY:
        editor.setCtrlKey(false);
        break;
    case SHIFT_KEY:
        editor.setShiftKey(false);
        break;
    }
}

