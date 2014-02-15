#!/bin/bash

# exit codes 
# 0 ok
# 1 system error
# 2 compilation error
# 3 wrong answer
# 4 execution error
# 5 time limit

problem=$1

g++ program.cpp -o program
if [ $? -ne 0 ]; then exit 2; fi

g++ ./$problem/solution.cpp -o solution
if [ $? -ne 0 ]; then exit 1; fi
g++ ./$problem/gen.cpp -o gen
if [ $? -ne 0 ]; then exit 1; fi

for i in `seq 1 20`; do
	./gen > input.out
	./solution < input.out > solution.out
	timeout 1s ./program < input.out > program.out
	lol=$?
	if [ $lol -eq 124 ]; then exit 5; fi
	if [ $lol -ne 0 ]; then exit 4; fi

	diff --ignore-case --ignore-all-space solution.out program.out >/dev/null 2>&1
	if [ $? -ne 0 ]; then exit 3; fi
done
