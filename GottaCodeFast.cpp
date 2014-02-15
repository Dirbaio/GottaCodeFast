#include "GottaCodeFast.hpp"
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

GottaCodeFast::GottaCodeFast(int scrwidth, int scrheight, std::string title, int style) : Game(scrwidth, scrheight, title, style), editor(this), ui(this) {
}

GottaCodeFast::~GottaCodeFast() {
}

void GottaCodeFast::update(float deltaTime) {
	editor.update(deltaTime);
	ui.update(deltaTime);
}

void GottaCodeFast::draw() {
	ui.draw();
	editor.draw(sf::Vector2f(250,100));
}

void GottaCodeFast::onMouseButtonPressed(sf::Event event) {
}

void GottaCodeFast::compile() {
	//TODO Cambiar
	std::string problem = "sum";

	editor.saveToFile("data/judge/program.cpp");
	int pid = fork();
	if(pid == 0) {
		execlp("/bin/bash", "/bin/bash", "data/judge/judge.sh", problem.c_str(), NULL);
		std::cout<<"EXECLP FAIL"<<std::endl;
	}

	int status;
	waitpid(pid, &status, 0);
	std::cout<<"Exited with "<<WEXITSTATUS(status)<<std::endl;
}

void GottaCodeFast::onKeyPressed(int key) {
	if(key == 8) ui.resetTime(5);
	switch(key) {
		case 27: window.close(); break;
		case 5: compile(); break;
		default: editor.process(key); break;
	}
}

