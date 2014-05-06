#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include<string>

class Problem
{
public:
    Problem(std::string problem);
    std::string name;
    std::string statement;
    std::string start;
    int timeLimit;
};

#endif // PROBLEM_HPP
