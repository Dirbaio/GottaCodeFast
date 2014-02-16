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

GottaCodeFast::GottaCodeFast(int scrwidth, int scrheight, std::string title, int style) : Game(scrwidth, scrheight, title, style), editor(this), ui(this), compiling(false) {
	problem = "helloworld";
	time = 0;

	ui.setStatement(readAll("data/judge/"+problem+"/problem.txt"));
	editor.setProgram(readAll("data/judge/"+problem+"/start.cpp"));
	std::ifstream in("data/judge/"+problem+"/settings.txt");
	int timeLimit;
	in>>timeLimit;
	in.close();
	ui.resetTime(timeLimit);

	timeUp = false;

	w.setPosition(sf::Vector2f(1000,100));
	w.setPosFinal(sf::Vector2f(100,100));
	s.setPosition(sf::Vector2f(500,100));
	s.setPosFinal(sf::Vector2f(500,200));
}

GottaCodeFast::~GottaCodeFast() {
}

void GottaCodeFast::update(float deltaTime) {
	editor.update(deltaTime);
	ui.update(deltaTime);

	w.update(deltaTime);
	s.update(deltaTime);

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

//			std::cout<<"Errors: "<<errors<<std::endl;
			close(errorfd);

			compilationFinished(WEXITSTATUS(status), errors);
		}
	}

	if(ui.timeUp() && !timeUp)
	{
		timeUp = true;
		ui.setMessage("Tiempo!", 2, sf::Color(255, 200, 0));
	}
}

void GottaCodeFast::draw() {
	ui.draw();
	editor.draw(sf::Vector2f(250, 95));
	window.draw(w);
	window.draw(s);
}

void GottaCodeFast::onMouseButtonPressed(sf::Event event) {
	w.isClicked(sf::Vector2f(event.mouseButton.x,event.mouseButton.y));
	s.isClicked(sf::Vector2f(event.mouseButton.x,event.mouseButton.y));
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
		window.close();
	else if(!timeUp)
	{
		if(key == 5)
			compile();
		else
			editor.process(key);
	}
}

