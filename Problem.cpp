#include "Problem.hpp"
#include <fstream>

std::string name;

std::string readAll(std::string file)
{
    std::ifstream in(file);
    std::string s, res;
    while(getline(in, s))
        res += s + "\n";
    in.close();
    return res;
}

Problem::Problem(std::string problem)
{
    this->name = problem;
    statement = readAll("data/judge/"+problem+"/problem.txt");
    start = readAll("data/judge/"+problem+"/start.cpp");

    std::ifstream in("data/judge/"+problem+"/settings.txt");
    in>>timeLimit;
    in.close();


}
