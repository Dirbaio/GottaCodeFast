#!/bin/bash

# exit codes 
# 0 ok
# 1 system error
# 2 compilation error
# 3 wrong answer
# 4 execution error
# 5 time limit

cd "$(dirname "$0")"
problem=$1
prog=$2

mkdir -p tmp

g++ tmp/$prog.cpp -o tmp/$prog
if [ $? -ne 0 ]; then exit 2; fi

g++ ./$problem/solution.cpp -o tmp/$prog.sol
if [ $? -ne 0 ]; then exit 1; fi
g++ ./$problem/gen.cpp -o tmp/$prog.gen
if [ $? -ne 0 ]; then exit 1; fi

for i in `seq 1 20`; do
	./tmp/$prog.gen > tmp/$prog.in
	./tmp/$prog.sol < tmp/$prog.in > tmp/$prog.cor
	timeout 1s ./tmp/$prog < tmp/$prog.in > tmp/$prog.out
	lol=$?
	if [ $lol -eq 124 ]; then exit 5; fi
	if [ $lol -ne 0 ]; then exit 4; fi

	diff --ignore-case --ignore-all-space tmp/$prog.cor tmp/$prog.out >/dev/null 2>&1
	if [ $? -ne 0 ]; then exit 3; fi
done
