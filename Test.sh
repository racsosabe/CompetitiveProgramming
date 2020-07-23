#!/bin/bash

g++ $1 grader.cpp -Wall -static -O2 -lm -m64 -s -w -std=gnu++17 -fmax-errors=512
g++ Gen.cpp -o Gen

for((i = 0; i < 500; i++)); do
	./Gen > int
	echo "Running on test $i"
	./a.out < int > out
	ver=$(cat out)
	if [ "$ver" != "Accepted" ]; then
		tc=$i
		break
	fi
done

if [ "$ver" != "Accepted" ]; then
	echo "$ver on test $tc"
	cat int
else
	echo $ver
fi
