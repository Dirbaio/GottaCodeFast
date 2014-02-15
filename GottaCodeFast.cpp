#include "GottaCodeFast.hpp"
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
GottaCodeFast::GottaCodeFast(int scrwidth, int scrheight, std::string title, int style) : Game(scrwidth, scrheight, title, style), editor(this), ui(this), compiling(false) {
}

GottaCodeFast::~GottaCodeFast() {
}

void GottaCodeFast::update(float deltaTime) {
	editor.update(deltaTime);
	ui.update(deltaTime);

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
			std::cout<<"Exited with "<<WEXITSTATUS(status)<<std::endl;
			compiling = false;

			std::string errors = "";

			char buf[256];
			while((ret = read(errorfd, buf, sizeof(buf))) > 0) {
				std::string s(buf, ret);
				errors += s;
			}

			std::cout<<"Errors: "<<errors<<std::endl;
			close(errorfd);
		}
	}
}

void GottaCodeFast::draw() {
	ui.draw();
	editor.draw(sf::Vector2f(250,100));
}

void GottaCodeFast::onMouseButtonPressed(sf::Event event) {
}

void GottaCodeFast::compile() {
	if(compiling) {
		std::cout<<"Already compiling!"<<std::endl;
		return;
	}

	compiling = true;

	//TODO Cambiar
	std::string problem = "sum";

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

	close(p[1]);
	errorfd = p[0];
}

void GottaCodeFast::onKeyPressed(int key) {
	if(key == 8) ui.resetTime(5);
	switch(key) {
		case 27: window.close(); break;
		case 5: compile(); break;
		default: editor.process(key); break;
	}
}

