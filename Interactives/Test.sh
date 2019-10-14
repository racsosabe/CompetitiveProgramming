#!/bin/bash

g++-7 $1 grader.cpp -o median_ioi00 -Wall -static -O2 -lm -m64 -s -w -std=gnu++17 -fmax-errors=512
g++ Gen.cpp -o gen
veredict="Accepted"
for((i=0; i < 1000 ; i++)); do
	./gen > int
	timeout 10 ./median_ioi00 < int > veredict.txt
	echo "Running on test $i"
	veredict=$(cat veredict.txt)
	if [ "$veredict" != "Accepted" ]; then
		break
	fi
done
if [ "$veredict" == "Accepted" ];then
	echo $veredict
else
	echo "$veredict on test $testcase"
	cat int
fi
